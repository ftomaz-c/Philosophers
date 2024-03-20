/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:07:18 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/20 11:09:26 by ftomazc          ###   ########.fr       */
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
		philosopher_requests_left_fork(sim, philo);
		philosopher_requests_right_fork(sim, philo);
		philosopher_is_eating(sim, philo);
		philosopher_is_sleeping(sim, philo);
	}
	return (NULL);
}


int	start_simulation(t_sim *sim)
{
	t_philo *philo;
	int		i;
	
	philo = malloc(sim->num_of_philosophers * sizeof(t_philo));
	if (!philo)
		return (0);
	sim->threads = malloc(sim->num_of_philosophers * sizeof(pthread_t));
	i = 0;
	while (i < sim->num_of_philosophers)
	{
		init_philosopher(sim, philo, i);
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