/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:21:52 by ftomazc           #+#    #+#             */
/*   Updated: 2024/04/22 17:18:28 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

/**
 * @brief Writes a string to the given file descriptor.
 * 
 * Outputs a null-terminated string `str` to a specified file descriptor `fd`, 
 * character by character. It leverages `ft_putchar_fd` to write each character,
 * thus it's suitable for outputting strings to various destinations (e.g.,
 * standard output, standard error) as determined by the file descriptor. The 
 * function does not add a newline character at the end of the string, offering 
 * more control over the formatting of the output.
 * 
 * @param str The null-terminated string to write.
 * @param fd The file descriptor to which the string is written.
 */
void	ft_putstr_fd(char *str, int fd);

/**
 * @brief Writes a character to the given file descriptor.
 * 
 * This function sends a single character `c` to the specified file descriptor
 * `fd`. It's a basic utility for character output, directly utilizing the 
 * `write` system call for this purpose. It's commonly used for writing to
 * standard output, standard error, or files, by specifying the appropriate file
 * descriptor.
 * 
 * @param c The character to write.
 * @param fd The file descriptor to which the character is written.
 */
void	ft_putchar_fd(char c, int fd);

/**
 * @brief Validates if a string contains only digits.
 * 
 * Iterates through a null-terminated string to check for digit-only content 
 * ('0'-'9'). The function returns true (1) if the string is non-empty and 
 * contains only digits. It returns false (0) for empty strings or if any 
 * non-digit characters are present. Designed for validating numeric input in 
 * string format without signs, decimals, or formatting characters.
 * 
 * @param str Null-terminated string to check.
 * 
 * @return 1 if the string is non-empty and digit-only; 0 otherwise.
 */
int		ft_isdigit(char	*str);

/**
 * @brief Simplified custom atoi function for specific use case.
 * 
 * Converts a string to an integer.
 *
 * @note This version is tailored for simplicity and assumes the input string
 * contains only numeric characters (0-9) with no signs (+/-) or non-numeric
 * characters.
 *
 * @param str Pointer to the null-terminated string to be converted.
 * @return The integer result of the conversion.
 */
int		ft_atoi(char *str);

long	elapsed_time(t_sim *sim);
void	print_stats(t_sim *sim, t_philo *philo);
void	print_philo_stats(t_sim *sim, t_philo *philo);

#endif