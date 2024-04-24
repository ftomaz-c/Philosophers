/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:05:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/24 12:16:53 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_simulation(t_sim *sim)
{
	int	i;

	if (sim->philosophers)
		free(sim->philosophers);
	if (sim->threads)
		free(sim->threads);
	if (sim->print_lock)
	{
		pthread_mutex_destroy(sim->print_lock);
		free(sim->print_lock);
	}
	i = 0;
	while (i < sim->num_of_philos)
	{
		if (sim->forks[i].mutex)
		{
			pthread_mutex_destroy(sim->forks[i].mutex);
			free(sim->forks[i].mutex);
		}
		i++;
	}
	if (sim->forks)
		free(sim->forks);
	free_queue(sim);
	pthread_mutex_destroy(sim->q_lock);
	free(sim->q_lock);
}

int	config_sim(t_sim *sim, char **argv)
{
	sim->num_of_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		sim->philos_meal_count = ft_atoi(argv[5]);
		if (sim->philos_meal_count <= 0)
			return (0);
	}
	else
		sim->philos_meal_count = 0;
	if (sim->num_of_philos <= 0 || sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0)
		return (0);
	sim->queues = malloc(sim->num_of_philos * sizeof(t_request));
	if (!sim->queues)
		return (0);
	memset(sim->queues, 0, sim->num_of_philos * sizeof(t_request));
	sim->q_lock = malloc(sizeof(pthread_mutex_t));
	if (!sim->q_lock)
		return (0);
	pthread_mutex_init(sim->q_lock, NULL);
	sim->sim_stop = false;
	return (1);
}

int	setup_simulation(t_sim *sim, char **args)
{
	if (!config_sim(sim, args))
	{
		error_message(4, NULL);
		exit(EXIT_FAILURE);
	}
	sim->philosophers = malloc(sim->num_of_philos * sizeof(t_philo));
	if (!sim->philosophers)
		return (0);
	sim->forks = malloc(sim->num_of_philos * sizeof(t_fork));
	if (!sim->forks)
		return (0);
	sim->threads = malloc(sim->num_of_philos * sizeof(pthread_t));
	if (!sim->threads)
		return (0);
	sim->print_lock = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(sim->print_lock, NULL) != 0)
		return (0);
	return (1);
}
