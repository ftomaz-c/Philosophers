/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:05:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/20 12:33:16 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	cleanup_simulation(t_sim *sim)
{
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
	config_sim(sim, args);
	gettimeofday(&sim->sim_time, NULL);
	sim->philosopher = malloc(sim->num_of_philosophers * sizeof(t_philo));
	if (!sim->philosopher)
		return (0);
	sim->threads = malloc(sim->num_of_philosophers * sizeof(pthread_t));
	if (!sim->philosopher)
	{
		free(sim->philosopher);
		return (0);
	}
	return (1);
}