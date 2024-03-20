#ifndef STRUCT_H
# define STRUCT_H

# include "philo.h"

typedef struct	s_sim
{
	int				num_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philosophers_meal_count;
	bool			sim_stop;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	struct timeval	sim_time;
}	t_sim;

typedef struct	s_philo
{
	int		id;
	int		meals_eaten;
	int		left_fork;
	int		right_fork;
	long	time_since_last_meal;
	bool	died;
	t_sim	*sim;
}	t_philo;

#endif