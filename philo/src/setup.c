/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:05:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/05/02 21:38:09 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_mutexes(t_sim *sim)
{
	int	i;

	cleanup_simulation(sim);
	pthread_mutex_destroy(&sim->print_lock);
	i = 0;
	while (i < sim->num_of_philos)
	{
		pthread_mutex_destroy(&sim->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->sim_lock);
}

void	cleanup_simulation(t_sim *sim)
{
	if (sim->philosophers)
		free(sim->philosophers);
	if (sim->forks)
		free(sim->forks);
}

int	config_sim(t_sim *sim, char **argv)
{
	int	i;

	i = 0;
	sim->num_of_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->philos_meal_count = -1;
	if (argv[5])
		sim->philos_meal_count = ft_atoi(argv[5]);
	if (sim->num_of_philos <= 0 || sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0
		|| sim->philos_meal_count <= 0)
	{
		error_message(4, NULL);
		return (0);
	}
	if (pthread_mutex_init(&sim->sim_lock, NULL))
		return (0);
	sim->sim_stop = false;
	sim->philo_died = false;
	sim->philos_full = 0;
	return (1);
}

int	setup_simulation(t_sim *sim, char **args)
{
	if (!config_sim(sim, args))
		return (0);
	sim->philosophers = malloc(sim->num_of_philos * sizeof(t_philo));
	if (!sim->philosophers)
	{
		cleanup_simulation(sim);
		return (0);
	}
	sim->forks = malloc(sim->num_of_philos * sizeof(t_fork));
	if (!sim->forks)
	{
		cleanup_simulation(sim);
		return (0);
	}
	if (pthread_mutex_init(&sim->print_lock, NULL))
		return (0);
	return (1);
}
