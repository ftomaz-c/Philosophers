/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/20 13:44:10 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	while (!sim->sim_stop && (philo->meals_eaten < sim->philosophers_meal_count 
		|| !philo->died))
	{
		printf("%li\t Philosopher %i is thinking\n", elapsed_time(sim),
		philo->id);
		if (philo->time_since_last_meal >= sim->time_to_die)
		{
			philosopher_dies(sim, philo);
			break;
		}
		philosopher_fork_request(sim, philo);
		philosopher_is_eating(sim, philo);
		philosopher_is_sleeping(sim, philo);
	}
	return (NULL);
}

int	init_fork(t_philo *philo)
{
	philo->fork = malloc(sizeof(t_fork));
	if (!philo->fork)
	{
		ft_putstr_fd("Error: Failed to allocate memory for philosopher's fork\n"
		, STDERR_FILENO);
		return (0);
	}
	philo->fork->mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo->fork->mutex)
	{
		ft_putstr_fd("Error: Failed to allocate memory for fork's mutex\n",
		STDERR_FILENO);
		return (0);
	}
	philo->fork->clean = false;
	if (philo->id == 0)
		philo->fork->clean = true;
	philo->has_fork = true;
	if (pthread_mutex_init(philo->fork->mutex, NULL) != 0)
	{
		ft_putstr_fd("Error: Failed to initiate fork's mutex\n", STDERR_FILENO);
		return (0);
	}
	pthread_mutex_lock(philo->fork->mutex);
	return (1);
}

int	init_philosopher(t_sim *sim, t_philo *philo, int i)
{
	philo[i].id = i;
	philo[i].meals_eaten = 0;
	philo[i].time_since_last_meal = 0;
	if (!init_fork(&philo[i]))
	{
		if (philo[i].fork)
		{
			if (philo[i].fork->mutex)
				free(philo[i].fork->mutex);
			free(philo[i].fork);
		}
		
		return (0);
	}
	philo[i].died = false;
	philo[i].sim = sim;
	return (1);
}

int	start_simulation(t_sim *sim)
{
	t_philo *philo;
	int		i;
	
	philo = sim->philosopher;
	i = 0;
	while (i < sim->num_of_philosophers)
	{
		if (!init_philosopher(sim, philo, i))
			return (0);
		if (pthread_create(&sim->threads[i], NULL, philosopher_routine,
		(void *)&philo[i]))
		{	
			error_message(5, NULL);
			break ;
		}
		i++;
	}
	i = 0;
	while (i < sim->num_of_philosophers)
		pthread_join(sim->threads[i++], NULL);
	print_stats(sim, philo);
	free(philo);
	return (1);
}
