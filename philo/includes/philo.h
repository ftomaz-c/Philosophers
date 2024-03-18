#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define DEFAULT "\033[0m"
# define RED "\033[31m"
# define YELLOW "\033[33m"

void	ft_putstr_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);

#endif