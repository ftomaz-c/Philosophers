/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/20 13:42:29 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	philosopher_is_eating(t_sim *sim, t_philo *philo)
{
	long	time;

	philo->time_since_last_meal = elapsed_time(sim);
	time = philo->time_since_last_meal;
	printf("%li\t Philosopher %i is eating\n", time, philo->id);
	usleep(sim->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&sim->forks[philo->left_fork]);
	pthread_mutex_unlock(&sim->forks[philo->right_fork]);
}

void	philosopher_is_sleeping(t_sim *sim, t_philo *philo)
{
	long	time;

	time = elapsed_time(sim);
	printf("%li\t Philosopher %i is sleeping\n", time, philo->id);
	usleep(sim->time_to_sleep * 1000);
}

void	philosopher_fork_request(t_sim *sim, t_philo *philo)
{
	long	time;

	if ()
	pthread_mutex_lock(&sim->forks[philo->left_fork]);
	time = elapsed_time(sim);
	printf("%li\t Philosopher %i has taken the left fork\n", time, philo->id);
}

void	philosopher_dies(t_sim *sim, t_philo *philo)
{
	long	time;

	time = elapsed_time(sim);
	printf("%li\t Philosopher %i died\n", time, philo->id);
	philo->died = true;
	sim->sim_stop = true;
}