/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/22 17:16:41 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_action(char *action, long time, t_philo *philo)
{
	pthread_mutex_lock(philo->sim->print_mesage);
	printf("%li\t Philosopher %i %s\n", time, philo->id, action);
	pthread_mutex_unlock(philo->sim->print_mesage);
}

void	acquire_fork(t_fork *fork)
{
	pthread_mutex_lock(fork->mutex);
}

void	philosopher_eats(t_philo *philo)
{
	int		left_id;
	int		right_id;
	long	time;

	left_id = philo->id;
	right_id = (philo->id + 1) % philo->sim->num_of_philos;
	if (philo->id == philo->sim->num_of_philos - 1)
	{
		acquire_fork(&philo->sim->forks[right_id]);
		acquire_fork(&philo->sim->forks[left_id]);
	}
	else
	{
		acquire_fork(&philo->sim->forks[left_id]);
		acquire_fork(&philo->sim->forks[right_id]);
	}
	time = elapsed_time(philo->sim);
	philo->time_since_last_meal = time;
	if (!philo->sim->sim_stop)
		print_action("is eating", time, philo);
	usleep(philo->sim->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->sim->forks[left_id].mutex);
	pthread_mutex_unlock(philo->sim->forks[right_id].mutex);
}

void	philosopher_sleeps(t_sim *sim, t_philo *philo)
{
	long	time;

	time = elapsed_time(sim);
	if (!sim->sim_stop)
		print_action("is sleeping", time, philo);
	usleep(sim->time_to_sleep * 1000);
}

void	philosopher_dies(t_sim *sim, t_philo *philo)
{
	long	time;

	sim->sim_stop = true;
	philo->died = true;
	time = elapsed_time(sim);
	print_action("died", time, philo);
}
