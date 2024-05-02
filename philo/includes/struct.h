/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:30:51 by ftomazc           #+#    #+#             */
/*   Updated: 2024/05/02 18:43:58 by ftomaz-c         ###   ########.fr       */
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
	int				philos_full;
	bool			sim_stop;
	bool			philo_died;
	struct timeval	sim_time;
	pthread_mutex_t	print_lock;
	t_philo			*philosophers;
	t_fork			*forks;
	pthread_t		god;
	pthread_mutex_t	sim_lock;
}	t_sim;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		time_since_last_meal;
	bool		died;
	t_fork		*right_fork;
	int			right_id;
	bool		has_right;
	t_fork		*left_fork;
	int			left_id;
	bool		has_left;
	t_sim		*sim;
	pthread_t	thread;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

#endif