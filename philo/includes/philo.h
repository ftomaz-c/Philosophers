#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include "utils.h"

# define DEFAULT "\033[0m"
# define RED "\033[31m"
# define YELLOW "\033[33m"

/**
 * Simulation settings for the Dining Philosophers problem.
 * 
 * @param num_of_philosophers Total philosophers.
 * @param time_to_die Max time (in msecs) without eating before a philosopher dies.
 * @param time_to_eat Eating duration.
 * @param time_to_sleep Sleeping duration.
 * @param philosophers_meal_count Optional. Number of times each philosopher must eat.
 * If not specified, the simulation runs until a philosopher dies.
 */
typedef struct	s_sim
{
	int	num_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	philosophers_meal_count;
}	t_sim;

/**
 * Philosopher in the Dining Philosophers simulation.
 *
 * @param id Id of the philosopher.
 * @param meals_eaten Counts meals consumed by the philosopher.
 */
typedef struct	s_philosopher
{
	int	id;
	int	meals_eaten;
}	t_philosopher;

/**
 * @brief Displays an error message based on the error code.
 * 
 * Prints a predefined error message to the standard error output, corresponding to
 * the error code provided. If the error code indicates an invalid argument, the 
 * function also prints the argument that caused the error. This function is designed
 * to inform the user about the nature of the error encountered during the execution
 * of the program.
 * 
 * @param err The error code indicating the type of error.
 * @param str The string argument that caused the error, applicable for certain error codes.
 */
void	error_message(int err, char *str);

/**
 * @brief Displays the usage message.
 * 
 * Prints the usage instructions for the program to the standard error output. This
 * includes information about the expected arguments and their format. An example command
 * is also provided to illustrate proper usage. This function is typically called when the
 * user provides incorrect arguments or requests help.
 */
void	usage_message(void);

/**
 * @brief Validates the command-line arguments.
 * 
 * Checks the number and format of the command-line arguments passed to the program.
 * Ensures there are the correct number of arguments and that each argument is a valid
 * digit-only string. This function uses `error_message` to inform the user of specific
 * errors related to argument count or format and displays the `usage message` if any error
 * is found.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * 
 * @return Returns 0 if all arguments are valid, 1 otherwise.
 */
int		error_check(int	argc, char **argv);

#endif