/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/20 17:36:23 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	while (!sim->sim_stop && (philo->meals_eaten < sim->philos_meal_count 
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
		philosopher_requests_handling(sim, philo);
		philosopher_is_sleeping(sim, philo);
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
		forks[i].req_by_left = false;
		forks[i].req_by_right = false;
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
	philo[i].left_fork = NULL;
	philo[i].waiting_for_forks = false;
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
	print_stats(sim, sim->philosophers);
	free(sim->philosophers);
	return (1);
}
