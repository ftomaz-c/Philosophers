/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/20 17:38:30 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	philosopher_is_eating(t_sim *sim, t_philo *philo)
{
	long	time;

	if (philo->left_fork && philo->right_fork)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		philo->time_since_last_meal = elapsed_time(sim);
		time = philo->time_since_last_meal;
		printf("%li\t Philosopher %i is eating\n", time, philo->id);
		usleep(sim->time_to_eat * 1000);
		philo->meals_eaten++;
		philo->left_fork->clean = false;
		philo->right_fork->clean = false;
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
}

void	philosopher_is_sleeping(t_sim *sim, t_philo *philo)
{
	long	time;

	time = elapsed_time(sim);
	printf("%li\t Philosopher %i is sleeping\n", time, philo->id);
	usleep(sim->time_to_sleep * 1000);
}

void	philosopher_requests_handling(t_sim *sim, t_philo *philo)
{
	int		left_id;
	int		right_id;

	left_id = (philo->id + 1) % sim->num_of_philos;
	right_id = (philo->id - 1 + sim->num_of_philos) % sim->num_of_philos;
	if (philo->left_fork && philo->left_fork->req_by_right 
	&& !philo->left_fork->clean)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		philo->left_fork->req_by_right = false;
		sim->philosophers[right_id].right_fork = philo->left_fork;
		sim->philosophers[right_id].right_fork->clean = true;
		philo->left_fork = NULL;
		pthread_mutex_unlock(&sim->philosophers[right_id].right_fork->mutex);
	}
	if (philo->right_fork && philo->right_fork->req_by_left 
	&& !philo->right_fork->clean)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		philo->right_fork->req_by_left = false;
		sim->philosophers[left_id].left_fork = philo->right_fork;
		sim->philosophers[left_id].left_fork->clean = true;
		philo->right_fork = NULL;
		pthread_mutex_unlock(&sim->philosophers[left_id].left_fork->mutex);
	}
}

void	philosopher_fork_request(t_sim *sim, t_philo *philo)
{
	long	time;
	int		left_id;
	int		right_id;

	left_id = (philo->id + 1) % sim->num_of_philos;
	right_id = (philo->id - 1 + sim->num_of_philos) % sim->num_of_philos;
	time = elapsed_time(sim);
	if (!philo->left_fork)
	{
		pthread_mutex_lock(&sim->forks[left_id].mutex);
		if (!sim->forks[left_id].req_by_right)
			sim->forks[left_id].req_by_right = true;
		pthread_mutex_unlock(&sim->forks[left_id].mutex);
		philo->waiting_for_forks = true;
		printf("%li\t Philosopher %i requested left fork\n", time, philo->id);
	}
	if (!philo->right_fork)
	{
		pthread_mutex_lock(&sim->forks[right_id].mutex);
		if (!sim->forks[right_id].req_by_left)
			sim->forks[right_id].req_by_left = true;
		pthread_mutex_unlock(&sim->forks[right_id].mutex);
		philo->waiting_for_forks = true;
		printf("%li\t Philosopher %i requested right fork\n", time, philo->id);
	}
}

void	philosopher_dies(t_sim *sim, t_philo *philo)
{
	long	time;

	time = elapsed_time(sim);
	printf("%li\t Philosopher %i died\n", time, philo->id);
	philo->died = true;
	sim->sim_stop = true;
}