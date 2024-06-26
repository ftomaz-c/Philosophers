/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/05/02 19:19:53 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_forks(t_fork *forks, int num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		{
			ft_putstr_fd("Error: Failed to initiate fork's mutex\n",
				STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_philosophers(t_sim *sim, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < sim->num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].time_since_last_meal = 0;
		philo[i].died = false;
		philo[i].sim = sim;
		philo[i].right_id = i;
		philo[i].left_id = i + 1;
		if (i == sim->num_of_philos - 1)
		{
			philo[i].right_id = 0;
			philo[i].left_id = i;
		}
		philo[i].right_fork = &sim->forks[philo[i].right_id];
		philo[i].left_fork = &sim->forks[philo[i].left_id];
		philo[i].has_left = false;
		philo[i].has_right = false;
		i++;
	}
}

int	start_simulation(t_sim *sim)
{
	int		i;

	if (!init_forks(sim->forks, sim->num_of_philos))
		return (0);
	init_philosophers(sim, sim->philosophers);
	i = 0;
	pthread_mutex_lock(&sim->sim_lock);
	gettimeofday(&sim->sim_time, NULL);
	pthread_mutex_unlock(&sim->sim_lock);
	while (i < sim->num_of_philos)
	{
		if (pthread_create(&sim->philosophers[i].thread, NULL,
				philosopher_routine, (void *)&sim->philosophers[i]))
		{
			error_message(5, NULL);
			break ;
		}
		i++;
	}
	pthread_create(&sim->god, NULL, god_routine, sim->philosophers);
	i = 0;
	while (i < sim->num_of_philos)
		pthread_join(sim->philosophers[i++].thread, NULL);
	pthread_join(sim->god, NULL);
	return (1);
}
