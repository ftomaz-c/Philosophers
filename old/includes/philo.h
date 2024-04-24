/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:21:23 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/24 12:15:02 by ftomazc          ###   ########.fr       */
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
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PINK "\033[95m"

/*error.c*/
void		error_message(int err, char *str);
void		usage_message(void);
int			error_check(int argc, char **argv);

/*setup.c*/
int			setup_simulation(t_sim *sim, char **args);
int			config_sim(t_sim *sim, char **argv);
void		cleanup_simulation(t_sim *sim);

/*routine.c*/
int			start_simulation(t_sim *sim);
int			init_philosophers(t_sim *sim, t_philo *philo, int i);
int			init_forks(t_fork *forks, int num_of_forks);
void		*philosopher_routine(void *arg);
bool		all_philosophers_satisfied(t_sim *sim);

/*actions.c*/
void		handle_forks(t_sim *sim, t_philo *philo);
void		philosopher_eats(t_sim *sim, t_philo *philo);
void		philosopher_sleeps(t_sim *sim, t_philo *philo);
void		philosopher_dies(t_sim *sim, t_philo *philo);
void		philosopher_thinks(t_sim *sim, t_philo *philo);

/*actions_utils.c*/
void		acquire_right_fork(t_sim *sim, t_philo *philo);
void		acquire_left_fork(t_sim *sim, t_philo *philo);
void		drop_forks(t_philo *philo);

/*queue.c*/
void		del_request(t_sim *sim, int fork_id);
t_request	*new_request(t_philo *philo, int fork_id);
void		add_to_queue(t_sim *sim, t_request *req);
void		add_new_request(t_sim *sim, t_philo *philo);
void	free_queue(t_sim *sim);

#endif