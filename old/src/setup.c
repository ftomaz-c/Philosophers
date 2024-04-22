/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:05:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/22 17:09:33 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_simulation(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_of_philos)
	{
		pthread_mutex_destroy(sim->forks[i].mutex);
		free(sim->forks[i].mutex);
		i++;
	}
	if (sim->forks)
		free(sim->forks);
	if (sim->philosophers)
		free(sim->philosophers);
	if (sim->threads)
		free(sim->threads);
}

void	config_sim(t_sim *sim, char **argv)
{
	sim->num_of_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		sim->philos_meal_count = ft_atoi(argv[5]);
		if (sim->philos_meal_count <= 0)
		{
			error_message(4, NULL);
			exit(EXIT_FAILURE);
		}
	}
	else
		sim->philos_meal_count = 0;
	if (sim->num_of_philos <= 0 || sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0)
	{
		error_message(4, NULL);
		exit(EXIT_FAILURE);
	}
	sim->sim_stop = false;
}

int	setup_simulation(t_sim *sim, char **args)
{
	config_sim(sim, args);
	sim->philosophers = malloc(sim->num_of_philos * sizeof(t_philo));
	if (!sim->philosophers)
		return (0);
	sim->forks = malloc(sim->num_of_philos * sizeof(t_fork));
	if (!sim->forks)
		return (0);
	sim->threads = malloc(sim->num_of_philos * sizeof(pthread_t));
	if (!sim->threads)
		return (0);
	sim->print_mesage = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(sim->print_mesage, NULL) != 0)
		return (0);
	return (1);
}
