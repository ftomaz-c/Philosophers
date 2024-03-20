#ifndef STRUCT_H
# define STRUCT_H

# include "philo.h"

typedef struct	s_philo t_philo;

typedef struct	s_fork
{
	bool			clean;
	pthread_mutex_t	*mutex;
}	t_fork;

typedef struct	s_sim
{
	int				num_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philosophers_meal_count;
	t_philo			*philosopher;
	pthread_t		*threads;
	struct timeval	sim_time;
	bool			sim_stop;
}	t_sim;

typedef struct	s_philo
{
	int		id;
	int		meals_eaten;
	t_fork	*fork;
	bool	has_fork;
	long	time_since_last_meal;
	bool	died;
	t_sim	*sim;
}	t_philo;

#endif