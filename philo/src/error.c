/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:25:59 by ftomazc           #+#    #+#             */
/*   Updated: 2024/05/02 16:14:00 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_message(int err, char *str)
{
	char	*error_message;

	ft_putstr_fd(RED"Error: ", STDERR_FILENO);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	if (err == 1)
		error_message = "Not enough arguments provided.\n"DEFAULT;
	else if (err == 2)
		error_message = "Too many arguments.\n"DEFAULT;
	else if (err == 3)
		error_message = " is an invalid argument.\n"DEFAULT;
	else if (err == 4)
		error_message = "Arguments must be positive integers.\n"DEFAULT;
	else if (err == 5)
		error_message = "Failed to create thread\n"DEFAULT;
	else if (err == 6)
		error_message = " failed to lock\n";
	else if (err == 7)
		error_message = " failed to unlock\n";
	else
		error_message = "Unexpected error occurred.\n"DEFAULT;
	ft_putstr_fd(error_message, STDERR_FILENO);
}

void	usage_message(void)
{
	char	*usage_message;

	usage_message = GREEN"Usage: ./philo arg1 arg2 arg3 arg4 [arg5 (optional)]\
	\n"DEFAULT
		"arg1: number_of_philosophers\n"
		"arg2: time_to_die (in msec)\n"
		"arg3: time_to_eat (in msec)\n"
		"arg4: time_to_sleep (in msec)\n"
		"arg5: number_of_times_each_philosopher_must_eat (opt)\n"
		"e.g.: ./philo 5 800 200 200 (3)\n";
	ft_putstr_fd(usage_message, STDERR_FILENO);
}

int	error_check(int argc, char **argv)
{
	int	i;
	int	error;

	error = 0;
	if (!(argc == 5 || argc == 6))
	{
		if (argc < 5)
			error_message(1, NULL);
		else
			error_message(2, NULL);
		error = 1;
	}
	i = 1;
	while (i < argc)
	{
		if (!ft_isdigit(argv[i]))
		{
			error_message(3, argv[i]);
			error = 1;
		}
		i++;
	}
	if (error)
		usage_message();
	return (error);
}
