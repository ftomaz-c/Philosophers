/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:18:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/24 12:18:10 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	acquire_right_fork(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(sim->forks[philo->right_id].mutex);
}

void	acquire_left_fork(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(sim->forks[philo->left_id].mutex);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->sim->forks[philo->right_id].mutex);
	pthread_mutex_unlock(philo->sim->forks[philo->left_id].mutex);
}