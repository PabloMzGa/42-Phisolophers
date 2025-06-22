/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:24:47 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 00:19:44 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

//////////////////////////////////// ENUMS /////////////////////////////////////
typedef enum e_philo_status
{
	HUNGRY = 0,
	FULL = 2
}								t_status;

//////////////////////////////////// STRUCS ////////////////////////////////////
/**
 * @struct s_args_info
 * @brief Structure to store simulation arguments for the philosophers problem.
 *
 * @param philo_n   Number of philosophers in the simulation.
 * @param time_die  Time (ms) a philosopher can go without eating before dying.
 * @param time_eat  Time (ms) a philosopher spends eating.
 * @param time_sleep Time (ms) a philosopher spends sleeping.
 * @param n_eat     Number of times each philosopher must eat before the
 *                  simulation ends. If set to -1, there is no limit.
 */
typedef struct s_args_info
{
	size_t						philo_n;
	long						time_die;
	size_t						time_eat;
	size_t						time_sleep;
	int							n_eat;
	long						epoch;
	int							simulation_running;
}								t_args;

/**
 * @struct s_philosophers_list
 * @brief Represents a node in the philosophers linked list.
 *
 * This structure is used to model a philosopher in the dining philosophers
 * problem. Each node contains pointers to the previous and next philosophers,
 * a unique identifier, thread and mutex for synchronization, a counter for the
 * number of times the philosopher has eaten, the philosopher's status, and a
 * pointer to shared arguments.
 *
 * @param previous Pointer to the previous philosopher in the list.
 * @param next Pointer to the next philosopher in the list.
 * @param id Id number of the philosopher.
 * @param thread Thread where the philosopher runs.
 * @param mutex Mutex for synchronizing access to the philosopher's data.
 * @param n_eat Number of times this philosopher has eaten.
 * @param status Current status of the philosopher.
 * @param args Pointer to shared arguments for the simulation.
 */
typedef struct s_philosophers_list
{
	struct s_philosophers_list	*previous;
	struct s_philosophers_list	*next;
	size_t						id;
	pthread_t					thread;
	pthread_mutex_t				mutex;
	int							n_eat;
	long						last_meal_timestamp;
	t_status					status;
	t_args						*args;
}								t_philo;

/////////////////////////////// PHILO MANAGEMENT ///////////////////////////////

/**
 * @brief Initializes a circular doubly linked list of philosophers.
 *
 * This function creates a list of philosopher structures based on the number
 * of philosophers specified in the `args` parameter. Each philosopher is
 * created using the `create_philo` function and added to the list using
 * `add_philo`. If memory allocation fails at any point, the function cleans
 * up any previously allocated philosophers using `clean_philos` and returns
 * NULL. The resulting list is circular: the last philosopher's `next` pointer
 * points to the first philosopher, and the first philosopher's `previous`
 * pointer points to the last philosopher.
 *
 * @param args Pointer to a structure containing the number of philosophers
 *             (`philo_n`).
 * @return Pointer to the first philosopher in the circular doubly linked list,
 *         or NULL if memory allocation fails.
 */
t_philo							*populate_philosophers(t_args *args);

/////////////////////////////// PHILO BEHAVIOUR ////////////////////////////////

/**
 * @brief Handles the eating behavior of a philosopher.
 *
 * This function manages the process where a philosopher attempts to eat.
 * It typically involves acquiring the necessary resources (such as forks),
 * updating the philosopher's state, and handling timing and synchronization
 * as required by the simulation rules.
 *
 * @param philo Pointer to the philosopher structure representing the current
 * philosopher.
 */
void							philosopher_eat(t_philo *philo);

/**
 * @brief Makes the philosopher sleep for a specified duration and then think.
 *
 * This function prints a message indicating that the philosopher is sleeping,
 * waits for the duration specified by args->time_sleep (in milliseconds),
 * and then prints a message indicating that the philosopher is thinking.
 *
 * @param philo Pointer to the philosopher structure.
 */
void							philosopher_sleep_think(t_philo *philo);

void							start_philosophers_behaviour(t_philo *philos);

/**
 * @brief Waits for the simulation to end based on philosophers' statuses.
 *
 * This function loops through the list of philosophers, checking their status.
 * The simulation continues running as long as not all philosophers have reached
 * the FULL status (i.e., have eaten the target number of times) and none of
 * them have reached the DEAD status. If all philosophers are FULL, a message is
 * printed to indicate the simulation is ending.
 *
 * @param philos Pointer to the first philosopher in the linked list.
 */
void							wait_philo_end(t_philo *philos);

//////////////////////////////////// UTILS /////////////////////////////////////

/**
 * @brief Gets the current time in milliseconds.
 *
 * This function retrieves the current system time using gettimeofday,
 * and returns the time in milliseconds since the Unix epoch.
 *
 * @return The current time in milliseconds as a long integer.
 */
long							get_time_ms(void);

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
int	check_args(int argc, char *argv[]);

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
int								ft_atoi(const char *nptr);

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
long							ft_atol(const char *nptr);

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
size_t							ft_atosize_t(const char *nptr);

/**
 * Checks if the given character is numeric.
 *
 * @param c The character to be checked.
 * @return 1 if the character is numeric, 0 otherwise.
 */
int								ft_isdigit(int c);

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
int								ft_isspace(char c);

////////////////////////// UTILS - PHILO LIST HELPERS //////////////////////////

/**
 * @brief Adds a new philosopher node to the end of the philosopher list.
 *
 * This function appends the given 'new' philosopher node to the end of the
 * doubly linked list pointed to by 'philo_lst'. If the list is empty,
 * 'new' becomes the first node. If either 'philo_lst' or 'new' is NULL,
 * the function does nothing.
 *
 * @param philo_lst Pointer to the head pointer of the philosopher list.
 * @param new Pointer to the new philosopher node to be added.
 */
void							add_philo(t_philo **philo_lst, t_philo *new);

/**
 * @brief Frees and cleans up a doubly-linked list of t_philo nodes.
 *
 * This function iterates through the linked list of t_philo structures,
 * starting from the given pointer, and frees each node. If the list is
 * doubly-linked, it ensures that the previous node's next pointer is set
 * to NULL to prevent dangling pointers. After cleanup, the original
 * pointer is set to NULL.
 *
 * @param philo Double pointer to the head of the t_philo list.
 */
void							clean_philos(t_philo **philo);

/**
 * @brief Creates and initializes a new philosopher structure.
 *
 * Allocates memory for a new t_philo instance, initializes its fields,
 * and sets up the mutex for the philosopher. The function sets the
 * philosopher's ID, resets the eat count, and links the provided
 * arguments structure. The next and previous pointers are initialized
 * to NULL.
 *
 * @param id    The unique identifier for the philosopher.
 * @param args  Pointer to the shared arguments structure.
 * @return      Pointer to the newly created t_philo structure,
 *              or NULL if memory allocation fails.
 */
t_philo							*create_philo(size_t id, t_args *args);

/**
 * @brief Searches for a philosopher node with the specified id in a circular
 * linked list.
 *
 * This function traverses a circular linked list of t_philo nodes, starting
 * from the given 'philos' pointer, and returns a pointer to the node whose
 * 'id' matches the specified 'id'. If no such node is found, or if the input
 * list is NULL, the function returns NULL.
 *
 * @param philos Pointer to the start of the circular linked list of t_philo
 * nodes.
 * @param id The id to search for within the list.
 * @return Pointer to the t_philo node with the matching id, or NULL if not
 * found.
 */
t_philo							*get_philo(t_philo *philos, size_t id);
#endif
