#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include "utils.h"

# define DEFAULT "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"

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

/*error.c*/
void	error_message(int err, char *str);
void	usage_message(void);
int		error_check(int	argc, char **argv);

#endif