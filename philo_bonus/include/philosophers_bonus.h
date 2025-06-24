/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:24:47 by pablo             #+#    #+#             */
/*   Updated: 2025/06/24 14:00:17 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
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
}								t_status;

//////////////////////////////////// STRUCS ////////////////////////////////////

/**
 * @struct s_args_info
 * @brief Structure holding simulation parameters for the philosophers problem.
 *
 * @param philo_n Number of philosophers in the simulation.
 * @param time_die Time (ms) a philosopher can go without eating before dying.
 * @param time_eat Time (ms) a philosopher spends eating.
 * @param time_sleep Time (ms) a philosopher spends sleeping.
 * @param n_eat Number of times each philosopher must eat before simulation
 *              ends. If negative, there is no limit.
 * @param epoch Timestamp marking the start of the simulation (ms).
 * @param simulation_running Flag: 1 if running, 0 if stopped.
 * @param simulation_mutex Mutex for synchronizing access to simulation_running.
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
	pthread_mutex_t				simulation_mutex;
	pthread_mutex_t				pritnf_mutex;
}								t_args;

/**
 * @struct s_philosophers_list
 * @brief Represents a philosopher in the dining philosophers problem.
 *
 * This structure holds all the necessary information for each philosopher,
 * including threading, synchronization primitives, state, and configuration.
 *
 * @param previous Pointer to the previous philosopher in the list (for circular
 *                 or doubly-linked list).
 * @param next Pointer to the next philosopher in the list.
 * @param id Unique identifier for the philosopher.
 * @param thread Thread handle for the philosopher's execution.
 * @param fork_mutex Mutex representing the fork held by this philosopher.
 * @param internal_mutex Mutex for synchronizing access to the philosopher's
 *                      internal state.
 * @param n_eat Number of times the philosopher has eaten.
 * @param last_meal_timestamp Timestamp of the last meal (in milliseconds or
 *                            appropriate time unit).
 * @param status Current status of the philosopher (e.g., thinking, eating,
 *               sleeping).
 * @param args Pointer to shared arguments or configuration for the simulation.
 *   Pointer to shared arguments or configuration for the simulation.
 */
typedef struct s_philosophers_list
{
	struct s_philosophers_list	*previous;
	struct s_philosophers_list	*next;
	size_t						id;
	pthread_t					thread;
	pthread_mutex_t				fork_mutex;
	pthread_mutex_t				internal_mutex;
	int							n_eat;
	long						last_meal_timestamp;
	t_status					status;
	t_args						*args;
}								t_philo;
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
int								check_philo_death(t_philo *philo);

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

/**
 * @brief Starts the behavior loop for all philosophers and monitors their
 *        state.
 *
 * This function initiates the main loop for philosopher threads, starts a
 * monitor thread to observe their status (e.g., for detecting death or
 * completion), and waits for all philosophers to finish their execution.
 * If the initial loop fails to start, the function returns early.
 *
 * @param philos Pointer to the array or structure representing the
 *        philosophers.
 */
void							start_philosophers_behaviour(t_philo *philos);

/**
 * @brief Starts a monitor thread for the philosopher simulation.
 *
 * This function creates a new thread that runs the monitor_routine,
 * passing the given philosopher structure as an argument. If thread
 * creation fails, it prints an error message, sets the simulation_running
 * flag to 0 (indicating the simulation should stop), and returns 0.
 *
 * @param philos Pointer to the t_philo structure representing the philosopher.
 * @return pthread_t The thread identifier of the created monitor thread,
 *         or 0 if thread creation failed.
 */
pthread_t						start_monitor(t_philo *philos);

/**
 * @brief Entry point for the philosopher thread behaviour.
 *
 * This function defines the main routine executed by each philosopher thread.
 * It optionally staggers the start of odd-numbered philosophers to avoid
 * contention, checks if the simulation is still running, and enters the main
 * behaviour loop. If the philosopher has eaten the required number of times,
 * it updates its status to FULL.
 *
 * @param args Pointer to a t_philo structure containing philosopher-specific
 * data.
 * @return Always returns NULL.
 */
void							*philosopher_behaviour(void *args);

/////////////////////////// PHILO BEHAVIOUR - UTILS ////////////////////////////

/**
 * @brief Selects the order of mutexes to avoid deadlock.
 *
 * This function assigns the addresses of two mutexes associated with the
 * philosopher's previous and next forks to the provided pointers, ensuring
 * a consistent locking order based on their memory addresses. This helps
 * prevent deadlocks when multiple philosophers attempt to lock forks.
 *
 * @param[out] first_mutex  Pointer to store the address of the first mutex
 *                          to lock.
 * @param[out] second_mutex Pointer to store the address of the second mutex
 *                          to lock.
 * @param[in]  philo        Pointer to the philosopher structure containing
 *                          fork mutexes.
 */
void							select_mutex(pthread_mutex_t **first_mutex,
									pthread_mutex_t **second_mutex,
									t_philo *philo);

/**
 * @brief Checks if the simulation should stop and unlocks mutexes if needed.
 *
 * This function checks the 'simulation_running' flag in the philosopher's
 * arguments. If the simulation is no longer running (i.e., the flag is 0),
 * it unlocks the provided mutexes (if they are not NULL) to ensure that any
 * held resources are released.
 *
 * @param philo   Pointer to the philosopher structure containing simulation
 *                state.
 * @param f_mutex Pointer to the first mutex to potentially unlock.
 * @param s_mutex Pointer to the second mutex to potentially unlock.
 * @return        1 if the simulation should stop and mutexes were unlocked,
 *                0 otherwise.
 */
int								check_stop(t_philo *philo,
									pthread_mutex_t *f_mutex,
									pthread_mutex_t *s_mutex);

//////////////////////////////////// UTILS /////////////////////////////////////

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
int								check_args(int argc, char *argv[]);

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
int								safe_mutex_lock(pthread_mutex_t *mutex,
									t_args *args);

/////////////////////////// UTILS - MUTEX OPERATIOS ////////////////////////////

/**
 * @brief Safely retrieves the current status of a philosopher.
 *
 * This function locks the internal mutex of the given philosopher to safely
 * access and return its status. If the mutex cannot be locked, it returns -1
 * to indicate an error.
 *
 * @param philo Pointer to the philosopher whose status is to be retrieved.
 * @return int The current status of the philosopher, or -1 on error.
 */
int								get_philo_status(t_philo *philo);

/**
 * @brief Gets the current value of simulation_running in a thread-safe manner.
 *
 * This function locks the simulation mutex, reads the value of
 * simulation_running, and then unlocks the mutex. This ensures that the
 * value is read safely without being modified by other threads. It is
 * used to check whether the simulation is currently running or not.
 *
 * @param args Pointer to the t_args structure containing the mutex and
 *             simulation_running variable.
 * @return int The current value of simulation_running (1 if running, 0 if
 *             not).
 */
int								get_simulation_running(t_args *args);

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
int								safe_mutex_unlock(pthread_mutex_t *mutex,
									t_args *args);

/**
 * @brief Safely prints a string to stdout using a mutex for sync.
 *
 * Locks the printf mutex before printing the string, ensuring only one
 * thread prints at a time. Unlocks the mutex after printing.
 * Returns 1 if mutex lock/unlock fails, 0 on success.
 *
 * @param string The string to print.
 * @param args Pointer to t_args with the printf mutex.
 * @return 0 on success, 1 on error.
 */
int								safe_single_printf(char *string, t_args *args);

/**
 * @brief Safely prints a formatted log message with timestamp and id,
 *        ensuring thread-safe access using a mutex.
 *
 * Locks the printf mutex before printing the message to prevent race
 * conditions in multi-threaded environments. Unlocks the mutex after
 * printing. Returns 1 if locking or unlocking fails.
 *
 * @param string The format string to print (should include placeholders
 *               for timestamp and id).
 * @param timestamp The timestamp value to include in the log message.
 * @param id The identifier to include in the log message.
 * @param args Pointer to the arguments structure containing the
 *             printf mutex.
 * @return Returns 0 on success, or 1 if mutex lock/unlock fails.
 */
int								safe_log_printf(char *string, long timestamp,
									size_t id, t_args *args);

/**
	* @brief Sets the simulation running state in a thread-safe manner.
	*
	* This function locks the simulation mutex,
		updates the simulation_running
	* flag in the provided t_args structure to the specified value, and then
	* unlocks the mutex. This ensures that the simulation_running flag is
	* safely updated in concurrent environments.
	*
	* @param args Pointer to the t_args structure containing the simulation state
	*             and mutex.
	* @param value The value to set for simulation_running (typically 0 or 1).
	*/
void							set_simulation_running(t_args *args, int value);

/**
 * @brief Safely sets the status of a philosopher by locking its internal mutex.
 *
 * This function acquires the internal mutex of the given philosopher to ensure
 * thread-safe modification of its status. If the mutex is successfully locked,
 * the status is updated and the mutex is subsequently unlocked.
 *
 * @param philo Pointer to the philosopher whose status is to be set.
 * @param status The new status value to assign to the philosopher.
 */
void							set_philo_status(t_philo *philo, int status);

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

#endif
