/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:21:30 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/20 12:19:13 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_sim			sim;
	
	if (error_check(argc, argv))
		exit (EXIT_FAILURE);
	if (!setup_simulation(&sim, argv))
	{
		ft_putstr_fd("Failed to setup simulation.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!start_simulation(&sim))
	{
		ft_putstr_fd("Failed to start simulation.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	cleanup_simulation(&sim);
	return(EXIT_SUCCESS);
}
