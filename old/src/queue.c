/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:26:08 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/24 12:29:56 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	del_request(t_sim *sim, int fork_id)
{
	t_request	*current;

	current = sim->queues[fork_id];
	if (sim->queues[fork_id])
	{
		sim->queues[fork_id] = sim->queues[fork_id]->next;
		free(current);
	}
}

void	free_queue(t_sim *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(sim->q_lock);
	while (i < sim->num_of_philos)
	{
		while (sim->queues[i])
			del_request(sim, i);
		i++;
	}
	free(sim->queues);
	pthread_mutex_unlock(sim->q_lock);
}

t_request	*new_request(t_philo *philo, int fork_id)
{
	t_request	*req;

	req = malloc(sizeof(t_request));
	if (!req)
		return (NULL);
	req->philosopher_id = philo->id;
	req->fork_id = fork_id;
	req->next = NULL;
	return (req);
}

void	add_to_queue(t_sim *sim, t_request *req)
{
	t_request	*current;

	current = sim->queues[req->fork_id];
	if (sim->queues[req->fork_id] == NULL)
		sim->queues[req->fork_id] = req;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = req;
	}
}

void	add_new_request(t_sim *sim, t_philo *philo)
{
	t_request	*right_req;
	t_request	*left_req;
	int			i;

	pthread_mutex_lock(sim->q_lock);
	right_req = new_request(philo, philo->right_id);
	left_req = new_request(philo, philo->left_id);
	if (!right_req || !left_req)
	{
		if (right_req)
			free(right_req);
		if (left_req)
			free(left_req);
		i = 0;
		while (i < sim->num_of_philos)
			pthread_join(sim->threads[i++], NULL);
		ft_putstr_fd("Error: Failed to add new requests to queue\n",
			STDERR_FILENO);
		cleanup_simulation(sim);
		exit (EXIT_FAILURE);
	}
	add_to_queue(sim, right_req);
	add_to_queue(sim, left_req);
	pthread_mutex_unlock(sim->q_lock);
}
