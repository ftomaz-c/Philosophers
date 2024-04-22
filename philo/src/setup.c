/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:05:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/20 18:18:43 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_simulation(t_sim *sim)
{
	if (sim->philosophers)
		free(sim->philosophers);
	if (sim->threads)
		free(sim->threads);
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
	sim->sim_stop = false;
	return (1);
}

int	config_manager(t_sim *sim, t_fork_manager *fork_manager)
{
	int	num_forks;
	int	i;

	fork_manager->num_of_forks = sim->num_of_philos;
	num_forks = fork_manager->num_of_forks;
	fork_manager->request_queue = malloc(num_forks * sizeof(t_request *));
	if (!fork_manager->request_queue)
		return(0);
	fork_manager->is_available = malloc(num_forks * sizeof(bool));
	if (!fork_manager->is_available)
		return(0);
	fork_manager->fork_mutexes = malloc(num_forks * sizeof(pthread_mutex_t));
	if (!fork_manager->fork_mutexes)
		return (0);
	i = 0;
	while (i < fork_manager->num_of_forks)
	{
		fork_manager->request_queue[i] = NULL;
		fork_manager->is_available[i] = true;
		pthread_mutex_init(&fork_manager->fork_mutexes[i], NULL);
		i++;
	}
	return (1);
}

int	setup_simulation(t_sim *sim, char **args)
{
	if (!config_sim(sim, args))
	{
		error_message(4, NULL);
		exit(EXIT_FAILURE);
	}
	gettimeofday(&sim->sim_time, NULL);
	sim->philosophers = malloc(sim->num_of_philos * sizeof(t_philo));
	if (!sim->philosophers)
		return (0);
	sim->threads = malloc(sim->num_of_philos * sizeof(pthread_t));
	if (!sim->threads)
		return (0);
	if (!config_manager(sim, sim->fork_manager))
		return (0);
	return (1);
}
