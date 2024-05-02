/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:18:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/05/02 21:21:29 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	custom_usleep(t_sim *sim, long actual_time, long time_to_action)
{
	while (elapsed_time(sim) < actual_time + time_to_action)
		usleep(100);
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
	if (!sim_check(philo->sim))
		print_log("has taken a fork", philo);
}

void	acquire_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	if (!sim_check(philo->sim))
		print_log("has taken a fork", philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}
