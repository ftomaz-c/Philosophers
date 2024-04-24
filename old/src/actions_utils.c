/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:18:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/24 14:41:04 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	acquire_right_fork(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(sim->forks[philo->right_id].mutex);
	//print_log(GREEN"has right fork"DEFAULT, philo);
}

void	acquire_left_fork(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(sim->forks[philo->left_id].mutex);
	//print_log(GREEN"has left fork"DEFAULT, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->sim->forks[philo->right_id].mutex);
	pthread_mutex_unlock(philo->sim->forks[philo->left_id].mutex);
}