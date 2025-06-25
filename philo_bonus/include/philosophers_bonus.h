/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:24:47 by pablo             #+#    #+#             */
/*   Updated: 2025/06/25 19:09:06 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h>
# include <limits.h>
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
}					t_status;

//////////////////////////////////// STRUCS ////////////////////////////////////

typedef struct s_args_info
{
	unsigned int	philo_n;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	n_eat;
	unsigned int	epoch;
	sem_t			*forks_sem;
	sem_t			*death_sem;
	sem_t			*full_sem;
	pthread_mutex_t	printf_mutex;
}					t_args;

typedef struct s_philosopher
{
	unsigned int	id;
	unsigned int	n_eat;
	unsigned int	last_meal_timestamp;
	pthread_mutex_t	internal_mutex;
	pid_t			pid;
	t_status		status;
	t_args			*args;
}					t_philo;

/////////////////////////////// PHILO BEHAVIOUR ////////////////////////////////

/**
 * @brief Checks if a philosopher has died due to starvation.
 *
 * This function safely reads the philosopher's last meal timestamp
 * and determines if the time elapsed since the last meal exceeds
 * the time_die threshold. If the philosopher has died, it prints
 * a death message and sets simulation_running to 0.
 *
 * @param philo Pointer to the philosopher to check.
 * @return int 1 if the philosopher has died, 0 otherwise
 */
int					check_philo_death(t_philo *philo);

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
void				philosopher_behaviour(t_philo *philo);

/**
 * @brief Simulates the eating behavior of a philosopher.
 *
 * This function makes the philosopher attempt to pick up two forks
 * (represented by semaphores), prints status messages for each action
 * (taking forks and eating), updates the timestamp of the last meal,
 * and increments the number of times the philosopher has eaten. The
 * philosopher will sleep for the duration specified by `time_eat` to
 * simulate eating.
 *
 * @param philo Pointer to the philosopher structure containing state
 * and arguments.
 */
void				philosopher_eat(t_philo *philo);

/**
 * @brief Makes the philosopher sleep for a specified duration and then think.
 *
 * This function logs to the console that the philosopher is sleeping,
 * waits for the configured sleep time (in milliseconds), and then logs
 * that the philosopher is thinking. The timestamps are relative to the
 * simulation epoch.
 *
 * @param philo Pointer to the philosopher structure containing its state
 * and arguments.
 */
void				philosopher_sleep_think(t_philo *philo);

void				start_philosophers_behaviour(t_philo *philo);

/**
 * @brief Starts the death monitor threads for the philosophers.
 *
 * This function creates two threads:
 *
 *  - One for monitoring the death condition of philosophers.
 *
 *  - Another for monitoring the stop condition related to death.
 *
 * If either thread fails to be created, an error message is printed and the
 * function returns 1.
 *
 * @param philos Pointer to the philosopher data structure to be passed to the
 * monitor threads.
 * @return int Returns 0 on success, or 1 if thread creation fails.
 */
int					start_death_monitors(t_philo *philos);

///////////////////////////////////// UTILS ////////////////////////////////////

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
int					check_args(int argc, char *argv[]);

/**
 * @brief Gets the current time in milliseconds.
 *
 * This function retrieves the current system time using gettimeofday,
 * and returns the time in milliseconds since the Unix epoch.
 *
 * @return The current time in milliseconds as a long integer.
 */
unsigned int		get_time_ms(void);

/////////////////////////// UTILS - MUTEX OPERATIOS ////////////////////////////

/**
 * @brief Safely locks a pthread mutex and handles errors.
 *
 * Attempts to lock the given mutex. If locking fails, prints an error
 * message and returns 1. If args is not NULL, also sets the
 * simulation_running flag to 0. Otherwise, returns 0 on success.
 *
 * @param mutex Pointer to the pthread_mutex_t to lock.
 * @param args Pointer to the t_args structure, used to signal simulation
 * status. Can be NULL to avoid modifying simulation_running.
 * @return int 0 on success, 1 on failure.
 */
int					safe_mutex_lock(pthread_mutex_t *mutex, t_args *args);

/**
 * @brief Safely unlocks a pthread mutex and handles errors.
 *
 * This function attempts to unlock the given mutex. If unlocking fails,
 * it prints an error message and returns 1. If args is not NULL, also
 * sets the simulation_running flag to 0 (indicating the simulation
 * should stop). On success, it returns 0.
 *
 * @param mutex Pointer to the pthread_mutex_t to unlock.
 * @param args Pointer to the t_args structure containing simulation state.
 * Can be NULL to avoid modifying simulation_running.
 * @return int 0 on success, 1 on failure.
 */
int					safe_mutex_unlock(pthread_mutex_t *mutex, t_args *args);

/**
 * @brief Safely prints a formatted log message with a timestamp and an ID,
 *        using a mutex for thread safety.
 *
 * This function locks the provided printf mutex before printing to ensure
 * that log messages from different threads do not interleave. It prints
 * the given string, substituting the elapsed time since the epoch and the
 * provided ID. After printing, it unlocks the mutex.
 *
 * @param string The format string to print (should contain two format
 *               specifiers: one for time, one for ID).
 * @param id     The identifier to include in the log message.
 * @param args   Pointer to a t_args structure containing the printf mutex
 *               and epoch time.
 * @return       0 on success, 1 if locking or unlocking the mutex fails.
 */
int					safe_log_printf(char *string, size_t id, t_args *args);

///////////////////////////////// UTILS - PARSE ////////////////////////////////

/**
 * @brief Converts a string to an unsigned int.
 *
 * Parses the string pointed to by @p nptr, skipping any leading whitespace
 * characters. Converts the subsequent numeric characters into an unsigned
 * integer value. If the string starts with a minus sign ('-'), the function
 * returns 0. If the string starts with a plus sign ('+'), it is ignored.
 * The conversion stops at the first non-digit character.
 *
 * @param nptr The string to convert.
 * @return The converted unsigned integer value, or 0 if the input is negative.
 */
unsigned int		ft_atoui(const char *nptr);

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
long				ft_atol(const char *nptr);

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
size_t				ft_atosize_t(const char *nptr);

/**
 * Checks if the given character is numeric.
 *
 * @param c The character to be checked.
 * @return 1 if the character is numeric, 0 otherwise.
 */
int					ft_isdigit(int c);

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
int					ft_isspace(char c);

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
void				clean_philo(t_philo *philo);

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
t_philo				*create_philo(size_t id, t_args *args);

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
t_philo				*populate_philosophers(t_args *args);

#endif
