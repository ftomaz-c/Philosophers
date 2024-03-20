#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include "struct.h"
# include "utils.h"

# define DEFAULT "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"

/*error.c*/
void	error_message(int err, char *str);
void	usage_message(void);
int		error_check(int	argc, char **argv);

/*setup.c*/
void	cleanup_simulation(t_sim *sim);
void	config_sim(t_sim *sim, char **argv);
int		setup_simulation(t_sim *sim, char **args);

/*routine.c*/
void	*philosopher_routine(void *arg);
int		start_simulation(t_sim *sim);

/*actions.c*/
void	philosopher_is_eating(t_sim *sim, t_philo *philo);
void	philosopher_is_sleeping(t_sim *sim, t_philo *philo);
void	philosopher_requests_left_fork(t_sim *sim, t_philo *philo);
void	philosopher_requests_right_fork(t_sim *sim, t_philo *philo);
void	philosopher_dies(t_sim *sim, t_philo *philo);

#endif