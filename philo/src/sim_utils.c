/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:18:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/26 19:10:40 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_died(t_sim *sim, t_philo *philo)
{
	if ((elapsed_time(sim) - philo->time_since_last_meal)
		>= sim->time_to_die)
	{
		drop_forks(philo);
		philosopher_dies(sim, philo);
		return (1);
	}
	return (0);
}

int	sim_check(t_sim *sim)
{
	pthread_mutex_lock(&sim->sim_lock);
	if (sim->sim_stop)
	{
		pthread_mutex_unlock(&sim->sim_lock);
		return (1);
	}
	pthread_mutex_unlock(&sim->sim_lock);
	return (0);
}

void	acquire_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
}

void	acquire_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}
