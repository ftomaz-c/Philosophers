/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:18:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/25 19:10:49 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	sim_check(t_sim *sim)
{
	pthread_mutex_lock(sim->sim_lock);
	if (sim->sim_stop)
	{
		pthread_mutex_unlock(sim->sim_lock);
		return (1);
	}
	pthread_mutex_unlock(sim->sim_lock);
	return (0);
}

void	acquire_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork->mutex);
}
	//print_log(GREEN"has right fork"DEFAULT, philo);

void	acquire_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork->mutex);
}
	//print_log(GREEN"has left fork"DEFAULT, philo);

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork->mutex);
	pthread_mutex_unlock(philo->left_fork->mutex);
}
