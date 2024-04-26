/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/26 20:21:21 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philosopher_eats(t_sim *sim, t_philo *philo)
{
	acquire_right_fork(philo);
	acquire_left_fork(philo);
	if (philo_died(sim, philo))
		return ;
	philo->time_since_last_meal = elapsed_time(philo->sim);
	print_log("is eating", philo);
	usleep(philo->sim->time_to_eat * 1000);
	if (philo_died(sim, philo))
		return ;
	philo->meals_eaten++;
	drop_forks(philo);
	if (sim->philos_meal_count != 0 && (sim->philos_meal_count
			== philo->meals_eaten))
	{
		pthread_mutex_lock(&sim->sim_lock);
		sim->philos_full++;
		pthread_mutex_unlock(&sim->sim_lock);
	}
	if (sim->philos_full == sim->num_of_philos)
	{
		pthread_mutex_lock(&sim->sim_lock);
		sim->sim_stop = true;
		pthread_mutex_unlock(&sim->sim_lock);
	}
}

void	philosopher_sleeps(t_sim *sim, t_philo *philo)
{
	if (!sim_check(sim))
	{
		print_log("is sleeping", philo);
		usleep(sim->time_to_sleep * 1000);
		if ((elapsed_time(sim) - philo->time_since_last_meal)
			>= sim->time_to_die)
		{
			philosopher_dies(sim, philo);
			return ;
		}
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
	if (sim_check(sim))
		return ;
	if ((elapsed_time(sim) - philo->time_since_last_meal)
		>= sim->time_to_die || sim->num_of_philos == 1)
	{
		if (sim->num_of_philos == 1)
			usleep(sim->time_to_die * 1000);
		pthread_mutex_lock(&sim->sim_lock);
		sim->sim_stop = true;
		pthread_mutex_unlock(&sim->sim_lock);
		philo->died = true;
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
	while (!sim_check(sim) && (philo->meals_eaten < sim->philos_meal_count
			|| !philo->died))
	{
		philosopher_dies(sim, philo);
		philosopher_eats(sim, philo);
		philosopher_sleeps(sim, philo);
		philosopher_thinks(sim, philo);
		usleep(1000);
	}
	return (NULL);
}
