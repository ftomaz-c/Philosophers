/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:21:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/26 16:27:30 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

void	ft_putstr_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_isdigit(char	*str);
int		ft_atoi(char *str);

long	elapsed_time(t_sim *sim);
void	print_stats(t_sim *sim, t_philo *philo);
void	print_philo_stats(t_sim *sim, t_philo *philo);
void	print_log(char *action, t_philo *philo);

#endif