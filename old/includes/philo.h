/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:21:23 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/22 17:00:02 by ftomaz-c         ###   ########.fr       */
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

/*error.c*/
void	error_message(int err, char *str);
void	usage_message(void);
int		error_check(int argc, char **argv);

/*setup.c*/
int		setup_simulation(t_sim *sim, char **args);
void	config_sim(t_sim *sim, char **argv);
void	cleanup_simulation(t_sim *sim);

int		start_simulation(t_sim *sim);
int		init_philosophers(t_sim *sim, t_philo *philo, int i);
int		init_forks(t_fork *forks, int num_of_forks);
void	*philosopher_routine(void *arg);
bool	all_philosophers_satisfied(t_sim *sim);

void	acquire_fork(t_fork *fork);
void	philosopher_eats(t_philo *philo);
void	philosopher_sleeps(t_sim *sim, t_philo *philo);
void	philosopher_dies(t_sim *sim, t_philo *philo);

void	print_action(char *action, long time, t_philo *philo);

#endif