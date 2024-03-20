/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:06:32 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/20 11:09:55 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	init_philosopher(t_sim *sim, t_philo *philo, int i)
{
	philo[i].id = i;
	philo[i].meals_eaten = 0;
	philo[i].time_since_last_meal = 0;
	philo[i].right_fork = philo[i].id;
	philo[i].left_fork = (philo[i].id + 1) % sim->num_of_philosophers;
	philo[i].died = false;
	philo[i].sim = sim;
}

long	elapsed_time(t_sim *sim)
{
	struct timeval	p_time;
	long			time;

	gettimeofday(&p_time, NULL);
	time = (p_time.tv_sec - sim->sim_time.tv_sec) * 1000 
	+ (p_time.tv_usec - sim->sim_time.tv_usec) / 1000;
	return (time);
}

void	print_stats(t_sim *sim, t_philo *philo)
{
	int i;
	
	printf("\n\t--------------------------------------------------\n");
	printf("\t-         Dining Philosophers Statistics         -\n");
	printf("\t--------------------------------------------------\n");
	printf("\t-                                                -\n");
	i = 0;
	while (i < sim->num_of_philosophers)
	{
		printf("\t-");
		if (philo[i].died)
			printf(RED"   X  ");
		else
			printf(GREEN"      ");
		printf("Philosopher %i\t\t%i\tmeals    "DEFAULT, philo[i].id,
		philo[i].meals_eaten);
		printf("-\n");
		i++;
	}
	printf("\t-                                                -\n");
	printf("\t--------------------------------------------------\n");
	printf("\t            Simulation run_time: %li           \n",
	elapsed_time(sim));
	printf("\t--------------------------------------------------\n");
	printf("\t                                   red - dead\n\n");
}