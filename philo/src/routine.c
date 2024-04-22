/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/05 12:44:28 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	all_philosophers_satisfied(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_of_philos)
	{
		if (sim->philosophers[i].meals_eaten < sim->philos_meal_count)
			return (false);
		i++;
	}
	return (true);
}

void	think(t_philo *philo)
{
	printf("%li\t Philosopher %i is thinking\n", elapsed_time(philo->sim),
		philo->id);
}

void	request_forks(t_philo *philo)
{
	int		left_fork_id;
	int		right_fork_id;

	left_fork_id = (philo->id + 1) % philo->sim->num_of_philos;
	right_fork_id = philo->id;
	if (left_fork_id < right_fork_id)
	{
		request_specific_fork(left_fork_id, philo);
		request_specific_fork(right_fork_id, philo);
	}
	else
	{
		request_specific_fork(right_fork_id, philo);
		request_specific_fork(left_fork_id, philo);
	}
	wait_for_fork(philo);
}

void	request_specific_fork(int fork_id, t_philo *philo)
{
	t_fork	*fork;

	fork = &philo->sim->forks[fork_id];
	while (true)
	{
		pthread_mutex_lock(&fork->lock);
		if (fork->owner_id != philo->id && !fork->request_id)
		{
			fork->request_id = philo->id;
			pthread_mutex_unlock(&fork->lock);
			break ;
		}
		pthread_mutex_unlock(&fork->lock);
		usleep(100);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		think(philo);
		request_forks(philo);
		break;
	}
	return (NULL);
}

int	init_forks(t_fork *forks, int num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		{
			ft_putstr_fd("Error: Failed to initiate fork's mutex\n",
				STDERR_FILENO);
			return (0);
		}
		forks[i].requested = false;
		forks[i].clean = false;
		i++;
	}
	return (1);
}

int	init_philosophers(t_sim *sim, t_philo *philo, int i)
{
	philo[i].id = i;
	philo[i].meals_eaten = 0;
	philo[i].time_since_last_meal = 0;
	philo[i].died = false;
	philo[i].sim = sim;
	philo[i].right_fork = &sim->forks[i];
	if (i == 0)
		sim->forks[i].clean = true;
	philo[i].left_fork = NULL;
	return (1);
}

int	start_simulation(t_sim *sim)
{
	int		i;

	i = 0;
	if (!init_forks(sim->forks, sim->num_of_philos))
		return (0);
	while (i < sim->num_of_philos)
	{
		if (!init_philosophers(sim, sim->philosophers, i))
			return (0);
		if (pthread_create(&sim->threads[i], NULL, philosopher_routine,
				(void *)&sim->philosophers[i]))
		{
			error_message(5, NULL);
			break ;
		}
		i++;
	}
	i = 0;
	while (i < sim->num_of_philos)
		pthread_join(sim->threads[i++], NULL);
	return (1);
}
