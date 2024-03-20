#ifndef STRUCT_H
# define STRUCT_H

# include "philo.h"

typedef struct	s_philo t_philo;

typedef struct	s_fork
{
	bool			req_by_left;
	bool			req_by_right;
	bool			clean;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct	s_sim
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philos_meal_count;
	t_philo			*philosophers;
	t_fork			*forks;
	pthread_t		*threads;
	struct timeval	sim_time;
	bool			sim_stop;
}	t_sim;

typedef struct	s_philo
{
	int		id;
	int		meals_eaten;
	t_fork	*left_fork;
	t_fork	*right_fork;
	long	time_since_last_meal;
	bool	died;
	t_sim	*sim;
	bool	waiting_for_forks;
}	t_philo;

#endif