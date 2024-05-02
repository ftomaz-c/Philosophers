/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:21:30 by ftomazc           #+#    #+#             */
/*   Updated: 2024/05/02 18:26:15 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (error_check(argc, argv))
		return (EXIT_FAILURE);
	if (!setup_simulation(&sim, argv))
	{
		ft_putstr_fd("Failed to setup simulation.\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!start_simulation(&sim))
	{
		destroy_mutexes(&sim);
		ft_putstr_fd("Failed to start simulation.\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	destroy_mutexes(&sim);
	return (EXIT_SUCCESS);
}

//print_stats(&sim, sim.philosophers);