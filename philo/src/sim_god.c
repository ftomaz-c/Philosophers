/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_god.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/05/02 19:47:01 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*god_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;
	int		i;

	philo = (t_philo *)arg;
	sim = philo[0].sim;
	while (1)
	{
		i = 0;
		while (i < sim->num_of_philos)
		{
			if (philo_check(sim, &philo[i]))
				return (NULL);
			i++;
		}
	}
}

int	philo_check(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(&sim->sim_lock);
	if (sim->philos_full == sim->num_of_philos)
	{
		sim->sim_stop = true;
		pthread_mutex_unlock(&sim->sim_lock);
		return (1);
	}
	if ((elapsed_time(sim) - philo->time_since_last_meal)
		>= sim->time_to_die)
	{
		pthread_mutex_unlock(&sim->sim_lock);
		philosopher_dies(sim, philo);
		return (1);
	}
	pthread_mutex_unlock(&sim->sim_lock);
	return (0);
}

void	philosopher_dies(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(&sim->sim_lock);
	sim->sim_stop = true;
	pthread_mutex_unlock(&sim->sim_lock);
	print_log("died", philo);
	return ;
}
