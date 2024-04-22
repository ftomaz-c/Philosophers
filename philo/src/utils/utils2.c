/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:06:32 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/02 17:15:54 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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
	printf("\n\t--------------------------------------------------\n");
	printf("\t-         Dining Philosophers Statistics         -\n");
	printf("\t--------------------------------------------------\n");
	printf("\t-                                                -\n");
	printf("\t-      Num. of Philosophers:\t%i                -\n",
		sim->num_of_philos);
	printf("\t-      Time to eat:\t\t%i              -\n",
		sim->time_to_eat);
	printf("\t-      Time to sleep:\t\t%i              -\n",
		sim->time_to_sleep);
	printf("\t-      Time to die:\t\t%i              -\n", sim->time_to_die);
	printf("\t-      Num. of Meals:\t\t%i                -\n",
		sim->philos_meal_count);
	if (sim->philos_meal_count == 0)
		printf("\t-                          0 - no limit of meals -\n");
	printf("\t-                                                -\n");
	print_philo_stats(sim, philo);
	printf("\t-                                                -\n");
	printf("\t--------------------------------------------------\n");
	printf("\t            Simulation run_time: %li           \n",
		elapsed_time(sim));
	printf("\t--------------------------------------------------\n");
	printf("\t                             green - survived\n");
	printf("\t                                   red - dead\n\n");
}

void	print_philo_stats(t_sim *sim, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < sim->num_of_philos)
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
}
