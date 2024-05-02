/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/05/02 21:23:14 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philosopher_eats(t_sim *sim, t_philo *philo)
{
	acquire_right_fork(philo);
	if (sim->num_of_philos == 1)
	{
		custom_usleep(sim, elapsed_time(sim), sim->time_to_die);
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
	pthread_mutex_unlock(&sim->sim_lock);
	print_log("is eating", philo);
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
	if (!sim_check(sim))
	{
		print_log("is sleeping", philo);
		custom_usleep(sim, elapsed_time(sim), philo->sim->time_to_sleep);
	}
}

void	philosopher_thinks(t_sim *sim, t_philo *philo)
{
	if (!sim_check(sim))
		print_log("is thinking", philo);
	custom_usleep(sim, elapsed_time(sim),
		sim->time_to_eat - sim->time_to_sleep);
	usleep(500);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	if (philo->id % 2 == 0 || (sim->num_of_philos % 2 != 0
			&& philo->id == sim->num_of_philos))
		philosopher_thinks(sim, philo);
	while (!sim_check(sim))
	{
		philosopher_eats(sim, philo);
		philosopher_sleeps(sim, philo);
		philosopher_thinks(sim, philo);
	}
	return (NULL);
}
