/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/30 21:04:21 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	custom_usleep(t_sim *sim, long actual_time, long time_to_eat)
{
	while (elapsed_time(sim) < actual_time + time_to_eat)
		usleep(100);
}

void	philosopher_eats(t_sim *sim, t_philo *philo)
{
	acquire_right_fork(philo);
	if (sim->num_of_philos == 1)
	{
		usleep(sim->time_to_die * 1000);
		drop_forks(philo);
		return ;
	}
	acquire_left_fork(philo);
	if (sim_check(sim))
	{
		drop_forks(philo);
		return ;
	}
	pthread_mutex_lock(&sim->sim_lock);
	philo->time_since_last_meal = elapsed_time(philo->sim);
	print_log("is eating", philo);
	pthread_mutex_unlock(&sim->sim_lock);
	custom_usleep(sim, elapsed_time(sim), philo->sim->time_to_eat);
	pthread_mutex_lock(&sim->sim_lock);
	philo->meals_eaten++;
	if (sim->philos_meal_count != 0 && (sim->philos_meal_count
		== philo->meals_eaten))
		sim->philos_full++;
	pthread_mutex_unlock(&sim->sim_lock);
	drop_forks(philo);
}

void	philosopher_sleeps(t_sim *sim, t_philo *philo)
{
	usleep(100);
	if (!sim_check(sim))
	{
		print_log("is sleeping", philo);
		usleep(sim->time_to_sleep * 1000);
	}
}

void	philosopher_thinks(t_sim *sim, t_philo *philo)
{
	(void)sim;
	if (!sim_check(sim))
		print_log("is thinking", philo);
}

void	philosopher_dies(t_sim *sim, t_philo *philo)
{
	if ((elapsed_time(sim) - philo->time_since_last_meal)
		>= sim->time_to_die)
	{
		sim->sim_stop = true;
		print_log("died", philo);
	}
	return ;
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (!sim_check(sim))
	{
		philosopher_eats(sim, philo);
		philosopher_sleeps(sim, philo);
		philosopher_thinks(sim, philo);
		//usleep(1000);
	}
	return (NULL);
}
