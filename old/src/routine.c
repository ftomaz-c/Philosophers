/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/22 17:16:32 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	all_philosophers_satisfied(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_of_philos)
	{
		if (sim->philosophers[i].meals_eaten < sim->philos_meal_count)
			return (false);
		i++;
	}
	return (true);
}


void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	if (sim->sim_time.tv_sec == 0 && sim->sim_time.tv_usec == 0)
		gettimeofday(&sim->sim_time, NULL);
	while (!sim->sim_stop && (philo->meals_eaten < sim->philos_meal_count
			|| !philo->died))
	{
		print_action("is thinking", elapsed_time(sim), philo);
		if ((elapsed_time(sim) - philo->time_since_last_meal)
			>= sim->time_to_die || sim->num_of_philos == 1 )
		{
			if (sim->num_of_philos == 1)
				usleep(sim->time_to_die * 1000);
			philosopher_dies(sim, philo);
			break ;
		}
		if (sim->philos_meal_count != 0 && (sim->philos_meal_count
			== philo->meals_eaten))
			break ;
		philosopher_eats(philo);
		philosopher_sleeps(sim, philo);
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
