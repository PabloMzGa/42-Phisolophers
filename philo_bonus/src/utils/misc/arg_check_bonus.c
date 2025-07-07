/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 00:14:10 by pablo             #+#    #+#             */
/*   Updated: 2025/07/07 17:40:17 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * @brief Checks if the given string represents a valid positive integer number.
 *
 * This function verifies that the input string is a valid representation of a
 * positive integer (greater than or equal to 1 and less than or equal to
 * UINT_MAX). It skips leading whitespace, allows an optional '+' sign, and
 * ensures all remaining characters are digits. Negative numbers, zero, and
 * non-numeric strings are considered invalid.
 *
 * @param str The input string to validate.
 * @return 1 if the string is a valid positive integer within the allowed range,
 *         0 otherwise.
 */
static int	is_valid_number(const char *str)
{
	int		i;
	long	long_n;

	if (!str)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	long_n = ft_atol(str);
	if (long_n > UINT_MAX || long_n < 1)
		return (0);
	return (1);
}

/**
 * @brief Validates that all command-line arguments are valid numbers.
 *
 * This function iterates through the command-line arguments (excluding the
 * program name) and checks if each argument is a valid number using the
 * is_valid_number() function. If any argument is not a valid number, it prints
 * an error message indicating the invalid argument and the valid range, then
 * returns 0. If all arguments are valid, it returns 1.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @return int Returns 1 if all arguments are valid numbers, 0 otherwise.
 */
static int	validate_argv_numbers(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf(RED "Error: Argument %d ('%s') is not a valid number!\n"
				RESET BOLD YELLOW
				"All arguments must be between 1 and %u.\n"
				RESET "\n", i, argv[i], UINT_MAX);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_args(int argc, char *argv[])
{
	if (argc < 5)
		return (printf(RED "Not enough arguments!\n" RESET BOLD "Usage: " RESET
				"./philo " ITALIC "n_philos t_die t_eat t_sleep"
				"[n_times_each_philo_must_eat]\n" RESET"\n"), 0);
	else if (argc > 6)
		return (printf(RED "Too many arguments!\n" RESET BOLD "Usage: " RESET
				"./philo " ITALIC "n_philos t_die t_eat t_sleep"
				" [n_times_each_philo_must_eat]\n" RESET "\n"), 0);
	if (!validate_argv_numbers(argc, argv))
		return (0);
	else
		return (validate_argv_numbers(argc, argv));
}
