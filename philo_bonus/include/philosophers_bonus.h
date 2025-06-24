/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:24:47 by pablo             #+#    #+#             */
/*   Updated: 2025/06/24 18:10:29 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

//////////////////////////////////// ENUMS /////////////////////////////////////
/**
 * @enum e_philo_status
 * @brief Represents the status of a philosopher.
 *
 * This enumeration defines the possible states a philosopher can be in:
 * - HUNGRY: The philosopher is hungry and wants to eat.
 * - FULL: The philosopher has eaten and is not hungry.
 */
typedef enum e_philo_status
{
	HUNGRY = 0,
	FULL = 1
}				t_status;

//////////////////////////////////// STRUCS ////////////////////////////////////

typedef struct s_args_info
{
	size_t		philo_n;
	long		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	int			n_eat;
	long		epoch;
	sem_t		*forks_sem;
	sem_t		*stop_sem;
	sem_t		*full_sem;
}				t_args;

typedef struct s_philosopher
{
	size_t		id;
	int			n_eat;
	long		last_meal_timestamp;
	pid_t		pid;
	t_status	status;
	t_args		*args;
}				t_philo;

/////////////////////////////// PHILO BEHAVIOUR ////////////////////////////////

/**
 * @brief Executes the main behaviour routine for a philosopher.
 *
 * This function introduces a slight delay for philosophers with odd IDs
 * to reduce contention when starting simultaneously. After the optional
 * delay, it enters the main behaviour loop for the philosopher.
 *
 * @param philo Pointer to the philosopher structure containing its state and
 *              arguments.
 */
void			philosopher_behaviour(t_philo *philo);

///////////////////////////////// UTILS - PARSE ////////////////////////////////

/**
 * @brief Converts a string to an integer.
 *
 * This function takes a string `nptr` and converts it to an integer. It skips
 * any leading whitespace characters and then checks for an optional sign
 * character ('-' or '+'). If a '-' sign is found, the resulting integer will
 * be negative. After that, it iterates through the string and converts each
 * digit character to its corresponding integer value. The function stops
 * converting when it encounters a non-digit character. The final result is
 * multiplied by the sign value and returned.
 *
 * @param nptr The string to be converted to an integer.
 * @return The converted integer value.
 */
int				ft_atoi(const char *nptr);

/**
 * @brief Converts a string to a long integer.
 *
 * This function parses the input string `nptr` and converts it to a long
 * integer. It handles optional leading whitespace, an optional '+' or '-'
 * sign, and numeric characters. If the input string contains non-numeric
 * characters after the numeric portion, they are ignored.
 *
 * @param nptr A pointer to the null-terminated string to be converted.
 *             The string may begin with whitespace and an optional sign.
 * @return The converted long integer value. If the string represents a
 *         negative number, the result will be negative.
 *
 * @note This function assumes that the input string is well-formed and does
 *       not handle overflow or invalid input errors.
 */
long			ft_atol(const char *nptr);

/**
 * @brief Converts a string to a size_t integer.
 *
 * Parses the input string, skipping any leading whitespace, and converts the
 * subsequent numeric characters into a size_t value. Handles an optional '+'
 * sign, but returns 0 if a '-' sign is encountered, as size_t cannot represent
 * negative values. Parsing stops at the first non-digit character.
 *
 * @param nptr The string to be converted.
 * @return The converted size_t value, or 0 if the string is negative or
 *         invalid.
 */
size_t			ft_atosize_t(const char *nptr);

/**
 * Checks if the given character is numeric.
 *
 * @param c The character to be checked.
 * @return 1 if the character is numeric, 0 otherwise.
 */
int				ft_isdigit(int c);

/**
 * @brief Checks if a character is a whitespace character.
 *
 * This function determines if the given character is a whitespace character.
 * Whitespace characters include space (' '), horizontal tab ('\t'),
 * vertical tab ('\v'), newline ('\n'), carriage return ('\r'),
 * and form feed ('\f').
 *
 * @param c The character to check.
 * @return 1 if the character is a whitespace character, 0 otherwise.
 */
int				ft_isspace(char c);

////////////////////////// UTILS - PHILO LIST HELPERS //////////////////////////

/**
 * @brief Cleans up resources associated with a philosopher.
 *
 * This function closes the semaphores used by the philosopher and frees
 * the dynamically allocated memory for the philosopher's arguments and
 * the philosopher structure itself.
 *
 * @param philo Pointer to the philosopher structure to be cleaned up.
 */
void			clean_philo(t_philo *philo);

/**
 * @brief Creates and initializes a new philosopher structure.
 *
 * Allocates memory for a new t_philo instance, sets its ID, initializes the
 * number of times eaten to zero, assigns the provided arguments pointer,
 * sets the initial status to HUNGRY, and records the current timestamp as
 * the last meal time.
 *
 * @param id    The unique identifier for the philosopher.
 * @param args  Pointer to the shared arguments structure.
 * @return      Pointer to the newly created t_philo structure, or NULL if
 *              memory allocation fails.
 */
t_philo			*create_philo(size_t id, t_args *args);

/**
 * @brief Populates philosopher structures and forks processes for each.
 *
 * Iterates over the number of philosophers in args. For each, creates a
 * philosopher structure with create_philo(), then forks. If in the parent,
 * frees the temporary philosopher and continues. If in the child, returns
 * the philosopher structure for further use.
 *
 * @param args Pointer to arguments structure with simulation parameters,
 *             including the number of philosophers (philo_n).
 * @return t_philo* Pointer to philosopher structure in the child process,
 *                  or NULL if all philosophers are created in the parent.
 */
t_philo			*populate_philosophers(t_args *args);


#endif
