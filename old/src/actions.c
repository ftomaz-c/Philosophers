/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/24 15:05:05 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	handle_forks(t_sim *sim, t_philo *philo)
{
	add_new_request(sim, philo);
	while (!sim->sim_stop)
	{
		if (!philo->has_right && sim->queues[philo->right_id]
			&& sim->queues[philo->right_id]->philosopher_id == philo->id)
		{
			acquire_right_fork(sim, philo);
			del_request(sim, philo->right_id);
			philo->has_right = true;
		}
		if (!philo->has_left && sim->queues[philo->left_id]
			&& sim->queues[philo->left_id]->philosopher_id == philo->id)
		{
			acquire_left_fork(sim, philo);
			del_request(sim, philo->left_id);
			philo->has_left = true;
		}
		if (philo->has_right && philo->has_left)
			break ;
	}
}

void	philosopher_eats(t_sim *sim, t_philo *philo)
{
	/*printf(PINK"-----%i time without eating before acquiring fork: %li\n"
		DEFAULT, philo->id, elapsed_time(philo->sim)
		- philo->time_since_last_meal);*/
	handle_forks(sim, philo);
	/*printf(PINK"-----%i time without eating after acquiring fork: %li\n"
		DEFAULT, philo->id, elapsed_time(philo->sim)
		- philo->time_since_last_meal);*/
	philosopher_dies(sim, philo);
	if (sim->sim_stop)
		return ;
	philo->time_since_last_meal = elapsed_time(philo->sim);
	print_log("is eating", philo);
	usleep(philo->sim->time_to_eat * 1000);
	philo->meals_eaten++;
	drop_forks(philo);
	if (sim->philos_meal_count != 0 && (sim->philos_meal_count
			== philo->meals_eaten))
		philo->philo_stop = true;
}

void	philosopher_sleeps(t_sim *sim, t_philo *philo)
{
	if (!sim->sim_stop)
		print_log("is sleeping", philo);
	usleep(sim->time_to_sleep * 1000);
	/*if (philo->id == 1)
		printf(BLUE"-----%i sleeped time: %li\n"DEFAULT, philo->id,
			elapsed_time(sim) - time);*/
}

void	philosopher_thinks(t_sim *sim, t_philo *philo)
{
	(void)sim;
	print_log("is thinking", philo);
}

void	philosopher_dies(t_sim *sim, t_philo *philo)
{
	if (sim->sim_stop)
		return ;
	if ((elapsed_time(sim) - philo->time_since_last_meal)
		>= sim->time_to_die || sim->num_of_philos == 1)
	{
		/*printf(RED"-----%i time without eating: %li\n"DEFAULT, philo->id,
			elapsed_time(sim) - philo->time_since_last_meal);*/
		if (sim->num_of_philos == 1)
			usleep(sim->time_to_die * 1000);
		sim->sim_stop = true;
		philo->died = true;
		print_log("died", philo);
	}
	return ;
}
