/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:21:23 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/20 18:16:54 by ftomazc          ###   ########.fr       */
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
int		config_sim(t_sim *sim, char **argv);
void	cleanup_simulation(t_sim *sim);

#endif