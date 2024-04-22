/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:30:51 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/22 17:16:50 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "philo.h"

typedef struct s_philo			t_philo;
typedef struct s_fork			t_fork;

typedef struct s_sim
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philos_meal_count;
	bool			sim_stop;
	struct timeval	sim_time;
	pthread_mutex_t	*print_mesage;
	t_philo			*philosophers;
	t_fork			*forks;
	pthread_t		*threads;
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

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
}	t_fork;

#endif