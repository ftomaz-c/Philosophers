/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:30:51 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/17 17:20:18 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "philo.h"

typedef struct s_philo			t_philo;
typedef struct s_fork_manager	t_fork_manager;

typedef struct s_sim
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philos_meal_count;
	t_philo			*philosophers;
	pthread_t		*threads;
	struct timeval	sim_time;
	bool			sim_stop;
	t_fork_manager	*fork_manager;
}	t_sim;

typedef struct s_philo
{
	int		id;
	int		meals_eaten;
	long	time_since_last_meal;
	bool	died;
	t_sim	*sim;
}	t_philo;

typedef struct s_request
{
	int					philosopher_id;
	struct s_request	*next;
}	t_request;

typedef struct s_fork_manager
{
	pthread_mutex_t	*fork_mutexes;
	int				num_of_forks;
	bool			*is_available;
	t_request		**request_queue;
}	t_fork_manager;

#endif