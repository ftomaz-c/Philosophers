/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:21:30 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/18 17:41:33 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	init_sim(t_sim *sim, char **argv)
{
	sim->num_of_philosophers = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		sim->philosophers_meal_count = ft_atoi(argv[5]);
	else
		sim->philosophers_meal_count = 0;
	
	printf("num: %i\n", sim->num_of_philosophers);
	printf("die: %i\n", sim->time_to_die);
	printf("eat: %i\n", sim->time_to_eat);
	printf("sleep: %i\n", sim->time_to_sleep);
	printf("meals: %i\n", sim->philosophers_meal_count);

}

int	main(int argc, char **argv)
{
	struct timeval	start;
	t_sim			sim;
	//t_philosopher	*philosophers;
	//pthread_t		*thread_id;
	
	if (error_check(argc, argv))
		exit (EXIT_FAILURE);
	init_sim(&sim, argv);
	gettimeofday(&start, NULL);
	return(EXIT_SUCCESS);
}