/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:21:23 by ftomazc           #+#    #+#             */
/*   Updated: 2024/05/02 19:48:44 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define RED "\033[91m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PINK "\033[95m"

/*error.c*/
void		error_message(int err, char *str);
void		usage_message(void);
int			error_check(int argc, char **argv);

/*setup.c*/
void		destroy_mutexes(t_sim *sim);
void		cleanup_simulation(t_sim *sim);
int			config_sim(t_sim *sim, char **argv);
int			setup_simulation(t_sim *sim, char **args);

/*sim_init.c*/
int			init_forks(t_fork *forks, int num_of_forks);
void		init_philosophers(t_sim *sim, t_philo *philo);
int			start_simulation(t_sim *sim);

/*sim.c*/
void		philosopher_eats(t_sim *sim, t_philo *philo);
void		philosopher_sleeps(t_sim *sim, t_philo *philo);
void		philosopher_thinks(t_sim *sim, t_philo *philo);
void		philosopher_dies(t_sim *sim, t_philo *philo);
void		*philosopher_routine(void *arg);

/*sim_god.c*/
void		*god_routine(void *arg);
int			philo_check(t_sim *sim, t_philo *philo);
void		philosopher_dies(t_sim *sim, t_philo *philo);

/*sim_utils.c*/
int			philo_check(t_sim *sim, t_philo *philo);
int			sim_check(t_sim *sim);
void		acquire_right_fork(t_philo *philo);
void		acquire_left_fork(t_philo *philo);
void		drop_forks(t_philo *philo);

#endif