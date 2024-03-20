/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:05:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/20 11:42:36 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	cleanup_simulation(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_of_philosophers)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->forks);
	free(sim->threads);
}

void	config_sim(t_sim *sim, char **argv)
{
	sim->num_of_philosophers = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		sim->philosophers_meal_count = ft_atoi(argv[5]);
		if (sim->philosophers_meal_count <= 0)
		{	
			error_message(4, NULL);
			exit(EXIT_FAILURE);
		}
	}
	else
		sim->philosophers_meal_count = 0;
	if (sim->num_of_philosophers <= 0 || sim->time_to_die <= 0 
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0)
	{	
		error_message(4, NULL);
		exit(EXIT_FAILURE);
	}
	sim->sim_stop = false;
}

int	setup_simulation(t_sim *sim, char **args)
{
	int	i;

	config_sim(sim, args);
	gettimeofday(&sim->sim_time, NULL);
	sim->forks = malloc(sim->num_of_philosophers * sizeof(pthread_mutex_t));
	if (!sim->forks)
		return (0);
	i = 0;
	while (i < sim->num_of_philosophers)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			exit (EXIT_FAILURE);
		i++;
	}
	return (1);
}