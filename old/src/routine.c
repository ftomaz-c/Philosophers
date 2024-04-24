/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/24 12:28:21 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	gettimeofday(&sim->sim_time, NULL);
	while (!sim->sim_stop && (philo->meals_eaten < sim->philos_meal_count
			|| !philo->died))
	{
		philosopher_dies(sim, philo);
		if (sim->sim_stop || philo->philo_stop)
			break ;
		philosopher_eats(sim, philo);
		if (sim->sim_stop || philo->philo_stop)
			break ;
		philosopher_sleeps(sim, philo);
		if (sim->sim_stop || philo->philo_stop)
			break ;
		philosopher_thinks(sim, philo);
		if (sim->sim_stop || philo->philo_stop)
			break ;
		usleep(100);
	}
	return (NULL);
}

int	init_forks(t_fork *forks, int num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
	{
		forks[i].mutex = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(forks[i].mutex, NULL) != 0)
		{
			ft_putstr_fd("Error: Failed to initiate fork's mutex\n",
				STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philosophers(t_sim *sim, t_philo *philo, int i)
{
	philo[i].id = i;
	philo[i].meals_eaten = 0;
	philo[i].time_since_last_meal = 0;
	philo[i].died = false;
	philo[i].sim = sim;
	philo[i].philo_stop = false;
	philo[i].right_id = i;
	philo[i].left_id = (i + 1) % sim->num_of_philos;
	philo[i].right_fork = &sim->forks[philo[i].right_id];
	philo[i].left_fork = &sim->forks[philo[i].left_id];
	philo[i].has_left = false;
	philo[i].has_right = false;
	return (1);
}

int	start_simulation(t_sim *sim)
{
	int		i;

	i = 0;
	if (!init_forks(sim->forks, sim->num_of_philos))
		return (0);
	while (i < sim->num_of_philos)
	{
		if (!init_philosophers(sim, sim->philosophers, i))
			return (0);
		if (pthread_create(&sim->threads[i], NULL, philosopher_routine,
				(void *)&sim->philosophers[i]))
		{
			error_message(5, NULL);
			break ;
		}
		i++;
	}
	i = 0;
	while (i < sim->num_of_philos)
		pthread_join(sim->threads[i++], NULL);
	return (1);
}
