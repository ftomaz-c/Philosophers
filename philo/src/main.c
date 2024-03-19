/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:21:30 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/19 17:40:03 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void	config_sim(t_sim *sim, char **argv)
{
	sim->num_of_philosophers = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		sim->philosophers_meal_count = ft_atoi(argv[5]);
		if (sim->philosophers_meal_count <= 0)
		{	
			error_message(4, NULL);
			exit(EXIT_FAILURE);
		}
	}
	else
		sim->philosophers_meal_count = 0;
	if (sim->num_of_philosophers <= 0 || sim->time_to_die <= 0 
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0)
	{	
		error_message(4, NULL);
		exit(EXIT_FAILURE);
	}
	sim->sim_stop = false;
}

long	elapsed_time(t_sim *sim)
{
	struct timeval	p_time;
	long			act_time;

	gettimeofday(&p_time, NULL);
	act_time = (p_time.tv_sec - sim->sim_time.tv_sec) * 1000 
	+ (p_time.tv_usec - sim->sim_time.tv_usec) / 1000;
	return (act_time);
}

void	print_stats(t_sim *sim, t_philo *philo)
{
	int i;
	
	printf("\n\t--------------------------------------------------\n");
	printf("\t-         Dining Philosophers Statistics         -\n");
	printf("\t--------------------------------------------------\n");
	printf("\t-                                                -\n");
	i = 0;
	while (i < sim->num_of_philosophers)
	{
		printf("\t-");
		if (philo[i].died)
			printf(RED"   X  ");
		else
			printf(GREEN"      ");
		printf("Philosopher %i\t\t%i\tmeals    "DEFAULT, philo[i].id,
		philo[i].meals_eaten);
		printf("-\n");
		i++;
	}
	printf("\t-                                                -\n");
	printf("\t--------------------------------------------------\n");
	printf("\t            Simulation run_time: %li           \n",
	elapsed_time(sim));
	printf("\t--------------------------------------------------\n");
	printf("\t                                   red - dead\n\n");
}

void	terminate_simulation(t_sim *sim, t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i < sim->num_of_philosophers)
	{
		pthread_join(sim->threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < sim->num_of_philosophers)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	print_stats(sim, philo);
	free(philo);
	free(sim->forks);
	free(sim->threads);
}

void	philosopher_is_eating(t_sim *sim, t_philo *philo)
{
	long	time;

	philo->time_since_last_meal = elapsed_time(sim);
	time = philo->time_since_last_meal;
	printf("%li\t Philosopher %i is eating\n", time, philo->id);
	usleep(sim->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&sim->forks[philo->left_fork]);
	pthread_mutex_unlock(&sim->forks[philo->right_fork]);
}

void	philosopher_is_sleeping(t_sim *sim, t_philo *philo)
{
	long	time;

	time = elapsed_time(sim);
	printf("%li\t Philosopher %i is sleeping\n", time, philo->id);
	usleep(sim->time_to_sleep * 1000);
}

void	philosopher_requests_left_fork(t_sim *sim, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&sim->forks[philo->left_fork]);
	time = elapsed_time(sim);
	printf("%li\t Philosopher %i has taken the left fork\n", time, philo->id);
}

void	philosopher_requests_right_fork(t_sim *sim, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&sim->forks[philo->right_fork]);
	time = elapsed_time(sim);
	printf("%li\t Philosopher %i has taken the right fork\n", time, philo->id);
}

void	philosopher_dies(t_sim *sim, t_philo *philo)
{
	long	time;

	time = elapsed_time(sim);
	printf("%li\t Philosopher %i died\n", time, philo->id);
	philo->died = true;
	sim->sim_stop = true;
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	while (!sim->sim_stop && (philo->meals_eaten < sim->philosophers_meal_count 
		|| !philo->died))
	{
		printf("%li\t Philosopher %i is thinking\n", elapsed_time(sim),
		philo->id);
		if (philo->time_since_last_meal >= sim->time_to_die)
		{
			philosopher_dies(sim, philo);
			break;
		}
		philosopher_requests_left_fork(sim, philo);
		philosopher_requests_right_fork(sim, philo);
		philosopher_is_eating(sim, philo);
		philosopher_is_sleeping(sim, philo);
	}
	return (NULL);
}

void	init_philosopher(t_sim *sim, t_philo *philo, int i)
{
	philo[i].id = i;
	philo[i].meals_eaten = 0;
	philo[i].time_since_last_meal = 0;
	philo[i].right_fork = philo[i].id;
	philo[i].left_fork = (philo[i].id + 1) % sim->num_of_philosophers;
	philo[i].died = false;
	philo[i].sim = sim;
}

int	init_sim(t_sim *sim, char **args)
{
	int	i;

	config_sim(sim, args);
	gettimeofday(&sim->sim_time, NULL);
	sim->forks = malloc(sim->num_of_philosophers * sizeof(pthread_mutex_t));
	if (!sim->forks)
		return (0);
	i = 0;
	while (i < sim->num_of_philosophers)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			exit (EXIT_FAILURE);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_sim			sim;
	t_philo			*philo;
	int				i;
	
	if (error_check(argc, argv))
		exit (EXIT_FAILURE);
	if (!init_sim(&sim, argv))
	{
		ft_putstr_fd("Failed to initialize simulation.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	philo = malloc(sim.num_of_philosophers * sizeof(t_philo));
	if (!philo)
	{
		ft_putstr_fd("Failed to setup simulation.\n", STDERR_FILENO);
		free(sim.forks);
		exit(EXIT_FAILURE);
	}
	sim.threads = malloc(sim.num_of_philosophers * sizeof(pthread_t));
	i = 0;
	while (i < sim.num_of_philosophers)
	{
		init_philosopher(&sim, philo, i);
		if (pthread_create(&sim.threads[i], NULL, philosopher_routine,
		(void *)&philo[i]))
		{	
			error_message(5, NULL);
			break ;
		}
		i++;
	}
	terminate_simulation(&sim, philo);
	return(EXIT_SUCCESS);
}
