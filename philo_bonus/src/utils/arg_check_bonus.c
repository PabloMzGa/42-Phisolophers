/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 00:14:10 by pablo             #+#    #+#             */
/*   Updated: 2025/06/24 15:46:54 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * @brief Checks if a string contains only positive numeric characters.
 *
 * This function validates that a string contains only valid positive numeric
 * characters. It allows for optional leading whitespace and an optional '+'
 * sign, but rejects negative numbers (those starting with '-').
 *
 * @param str The string to validate.
 * @return int Returns 1 if the string is a valid positive number, 0 otherwise.
 */
static int	is_valid_number(const char *str)
{
	int	i;

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
	return (1);
}

/**
 * @brief Validates that all command-line arguments contain only numeric values.
 *
 * This function checks that each argument from argv[1] onwards contains only
 * valid numeric characters. It skips argv[0] (program name) and validates
 * each subsequent argument.
 *
 * @param argc The number of command-line arguments.
 * @param argv The argument vector.
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
				RESET BOLD "All arguments must be positive integers.\n\n"
				RESET, i, argv[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief Checks the validity of command-line arguments for the philosophers
 * program.
 *
 * This function verifies that the number of arguments provided to the program
 * is within the expected range and that all arguments contain only valid
 * numeric values. It prints an error message and usage instructions if the
 * arguments are incorrect.
 *
 * @param argc The number of command-line arguments.
 * @param argv The argument vector.
 * @return int Returns 0 if the arguments are invalid, 1 otherwise.
 */
int	check_args(int argc, char *argv[])
{
	if (argc < 5)
		return (printf(RED "Not enough arguments!\n" RESET BOLD "Usage: " RESET
				"./philo " ITALIC "n_philos t_die t_eat t_sleep"
				" [n_times_each_philo_must_eat]\n\n" RESET), 0);
	else if (argc > 6)
		return (printf(RED "Too many arguments!\n" RESET BOLD "Usage: " RESET
				"./philo " ITALIC "n_philos t_die t_eat t_sleep"
				" [n_times_each_philo_must_eat]\n\n" RESET), 0);
	if (!validate_argv_numbers(argc, argv))
		return (0);
	else
		return (validate_argv_numbers(argc, argv));
}
