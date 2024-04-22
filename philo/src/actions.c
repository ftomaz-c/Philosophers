/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/02 17:34:48 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	acquire_fork(t_fork *fork, t_philo *philo, char *fork_side)
{
	pthread_mutex_lock(&fork->mutex);
	if (!fork->clean)
	{
		printf("%li\t Philosopher %i is cleaning the %s fork\n",
			elapsed_time(philo->sim), philo->id, fork_side);
		fork->clean = true;
	}
	printf("%li\t Philosopher %i has taken the %s fork\n",
		elapsed_time(philo->sim), philo->id, fork_side);
}

void	philosopher_eats(t_philo *philo)
{
	t_sim	*sim;
	int		left_id;
	int		right_id;
	long	time;


	sim = philo->sim;
	left_id = philo->id;
	right_id = (philo->id + 1) % sim->num_of_philos;
	if (philo->id == sim->num_of_philos - 1)
	{
		acquire_fork(&sim->forks[right_id], philo, "right");
		acquire_fork(&sim->forks[left_id], philo, "left");
	}
	else
	{
		acquire_fork(&sim->forks[left_id], philo, "left");
		acquire_fork(&sim->forks[right_id], philo, "right");
	}
	time = elapsed_time(sim);
	philo->time_since_last_meal = elapsed_time(sim);
	printf("%li\t Philosopher %i is eating\n", time, philo->id);
	usleep(sim->time_to_eat * 1000);
	//printf("%i eating time: %li\n", philo->id, elapsed_time(sim) - time);
	philo->meals_eaten++;
	sim->forks[left_id].clean = false;
	sim->forks[right_id].clean = false;
	pthread_mutex_unlock(&sim->forks[left_id].mutex);
	pthread_mutex_unlock(&sim->forks[right_id].mutex);
}

void	philosopher_sleeps(t_sim *sim, t_philo *philo)
{
	long	time;

	time = elapsed_time(sim);
	printf("%li\t Philosopher %i is sleeping\n", time, philo->id);
	usleep(sim->time_to_sleep * 1000);
	//printf("%i sleeped time: %li\n", philo->id, elapsed_time(sim) - time);
}

void	philosopher_dies(t_sim *sim, t_philo *philo)
{
	long	time;

	time = elapsed_time(sim);
	printf("%li\t Philosopher %i died\n", time, philo->id);
	philo->died = true;
	sim->sim_stop = true;
}
