/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:21:30 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/18 15:21:22 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc < 5)
	{
		ft_putstr_fd(RED"Error: Not enough arguments provided.\n"DEFAULT,
		 STDERR_FILENO);
		ft_putstr_fd(YELLOW"Usage: ./philo arg1 arg2 arg3 arg4 arg5(optional)\n\
"DEFAULT, STDERR_FILENO);
		ft_putstr_fd("arg1: number_of_philosophers\n", STDERR_FILENO);
		ft_putstr_fd("arg2: time_to_die (in milliseconds)\n", STDERR_FILENO);
		ft_putstr_fd("arg3: time_to_eat (in milliseconds)\n", STDERR_FILENO);
		ft_putstr_fd("arg4: time_to_sleep (in milliseconds)\n", STDERR_FILENO);
		ft_putstr_fd("arg5: number_of_times_each_philosopher_must_eat (optional\
argument)\n", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	return(0);
}