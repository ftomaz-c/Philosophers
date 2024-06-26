/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:30:51 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/24 11:59:49 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "philo.h"

typedef struct s_philo			t_philo;
typedef struct s_fork			t_fork;
typedef struct s_request		t_request;

typedef struct s_sim
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philos_meal_count;
	bool			sim_stop;
	struct timeval	sim_time;
	pthread_mutex_t	*print_lock;
	t_philo			*philosophers;
	t_fork			*forks;
	t_request		**queues;
	pthread_mutex_t	*q_lock;
	pthread_t		*threads;
}	t_sim;

typedef struct s_philo
{
	int		id;
	int		meals_eaten;
	long	time_since_last_meal;
	bool	philo_stop;
	bool	died;
	int		right_id;
	bool	has_right;
	t_fork	*right_fork;
	int		left_id;
	bool	has_left;
	t_fork	*left_fork;
	t_sim	*sim;
}	t_philo;

typedef struct s_request
{
	int					philosopher_id;
	int					fork_id;
	struct s_request	*next;
}	t_request;

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
}	t_fork;

#endif