/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:24:47 by pablo             #+#    #+#             */
/*   Updated: 2025/07/08 13:57:55 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define MICROSLEEP_MS 10

//////////////////////////////////// ENUMS /////////////////////////////////////

/**
 * @struct s_args_info
 * @brief Structure holding configuration and synchronization primitives for
 *        the philosophers simulation.
 *
 * @param philo_n    Number of philosophers participating in the simulation.
 * @param time_die   Time (in ms) a philosopher can go without eating before
 *                   dying.
 * @param time_eat   Time (in ms) a philosopher spends eating.
 * @param time_sleep Time (in ms) a philosopher spends sleeping.
 * @param n_eat      Number of times each philosopher must eat before the
 *                   simulation ends. If zero, there is no limit.
 * @param epoch      Timestamp marking the start of the simulation (used for
 *                   time calculations).
 * @param forks_sem  Semaphore used to control access to forks (shared
 *                   resources).
 * @param printf_sem Semaphore used to synchronize output to prevent message
 *                   interleaving.
 * @param stop_sem   Semaphore used to signal the end of the simulation (e.g.,
 *                   when a philosopher dies).
 * @param full_sem   Semaphore used to track when all philosophers have eaten
 *                   the required number of times.
 */
typedef struct s_args_info
{
	unsigned int	philo_n;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	n_eat;
	unsigned int	epoch;
	sem_t			*forks_sem;
	sem_t			*printf_sem;
	sem_t			*stop_sem;
	sem_t			*full_sem;
}					t_args;

/**
 * @struct s_philosopher
 * @brief Represents a philosopher in the dining philosophers simulation.
 *
 * @param id                     Unique identifier for the philosopher.
 * @param n_eat                  Number of times the philosopher has eaten.
 * @param last_meal_timestamp    Timestamp of the philosopher's last meal
 *                              (in milliseconds).
 * @param last_meal_sem          Semaphore to protect access to
 *                              last_meal_timestamp.
 * @param local_stop             Flag indicating if the philosopher should stop
 *                              (local to the philosopher).
 * @param local_stop_sem         Semaphore to protect access to local_stop.
 * @param death_monitor_end_sem  Semaphore used to signal the end of the death
 *                              monitoring process.
 * @param pid                    Process ID of the philosopher (used for
 *                              process management).
 * @param args                   Pointer to shared simulation arguments and
 *                              configuration.
 */
typedef struct s_philosopher
{
	unsigned int	id;
	unsigned int	n_eat;
	unsigned int	last_meal_timestamp;
	sem_t			*last_meal_sem;
	unsigned int	local_stop;
	sem_t			*local_stop_sem;
	sem_t			*death_monitor_end_sem;
	pid_t			pid;
	t_args			*args;
}					t_philo;

////////////////////////////// PHILO - BEHAVIOUR ///////////////////////////////

/**
 * @brief Starts the philosopher processes.
 *
 * This function iterates through the number of philosophers specified in the
 * arguments, creates a philosopher structure for each, and forks a new process
 * for each philosopher. If philosopher creation or forking fails, it handles
 * cleanup and returns an error code.
 *
 * @param args Pointer to the arguments structure containing simulation
 *             parameters.
 * @return int Returns 0 on success, 1 on failure.
 */
int					philo_start(t_args *args);

/**
 * @brief Handles the fork pick up and eating behavior of a philosopher.
 *
 * This function manages the process of a philosopher attempting to eat.
 * It first checks if the philosopher should stop (using get_local_stop).
 * If not, it attempts to pick up the first fork. If the philosopher is alone,
 * it returns early since eating is not possible. Otherwise, it attempts to
 * pick up the second fork and then proceeds to handle the eating process.
 *
 * @param philo Pointer to the philosopher structure.
 * @return int Returns 1 if the philosopher should stop or failed to pick up a
 *         fork, 0 if the eating process was handled successfully or if the
 *         philosopher is alone.
 */
int					philo_eat(t_philo *philo);

/**
 * @brief Checks if the philosopher has died based on the time since their last
 * meal.
 *
 * This function retrieves the current time and the time of the philosopher's
 * last meal, then determines if the philosopher should be considered dead
 * according to the simulation's rules.
 *
 * @param philo Pointer to the philosopher structure whose death status is being
 * checked.
 * @return int Returns a non-zero value if the philosopher has died, otherwise
 * returns 0.
 */
int					check_philo_death(t_philo *philo);

/**
 * @brief Main loop for philosopher behavior in the dining philosophers
 *        problem.
 *
 * This function represents the main execution loop for a philosopher
 * thread/process. It repeatedly checks if the philosopher should stop,
 * attempts to eat, handles the case where only one fork is available,
 * manages semaphore limits, and performs sleeping and thinking actions.
 * The loop continues until a stop condition is met or an action
 * (eating, sleeping, or thinking) signals to break the loop.
 *
 * @param args Pointer to a t_philo structure containing philosopher state
 *        and arguments.
 * @return Always returns NULL.
 */
void				*philo_behaviour_loop(void *args);

/**
 * @brief Handles the sleeping and thinking behavior of a philosopher.
 *
 * This function manages the transition of a philosopher to the sleeping state,
 * waits for the specified sleep duration, and then transitions the philosopher
 * to the thinking state. It also introduces a small, variable delay before
 * thinking to help reduce contention between philosophers.
 *
 * The function checks for a local stop condition before and after sleeping,
 * and returns early if the philosopher should stop. Logging is performed for
 * both sleeping and thinking states.
 *
 * @param philo Pointer to the philosopher structure.
 * @return int Returns 1 if a stop condition is detected, otherwise 0.
 */
int					philo_sleep_think(t_philo *philo);

/////////////////////////////// PHILO - MONITOR ////////////////////////////////

/**
 * @brief Monitors the death status of a philosopher in a concurrent
 * environment.
 *
 * This function runs as a separate thread for each philosopher. It
 * continuously checks if the philosopher has died or if a local stop
 * condition has been triggered. If a local stop is detected, it signals
 * the end of the death monitor and exits. If the philosopher dies, it
 * posts to the stop semaphore for all philosophers to signal termination,
 * then signals the end of the death monitor.
 *
 * @param args Pointer to the philosopher structure (t_philo *).
 * @return NULL Always returns NULL after signaling the end of the monitor.
 */
void				*death_monitor(void *args);

/**
 * @brief Monitor function to handle the stopping condition for philosophers.
 *
 * This function waits on the stop semaphore to be signaled, indicating that the
 * simulation should stop (e.g., a philosopher has died or the simulation is
 * complete). Once the semaphore is acquired,
	it sets the local stop flag for the
 * philosopher. If a required number of meals (`n_eat`) is specified,
	it posts to
 * the full semaphore for each philosopher to signal completion.
 *
 * @param args Pointer to a t_philo structure representing the philosopher.
 * @return Always returns NULL.
 */
void				*stop_monitor(void *args);

/**
 * @brief Monitors when all philosophers have finished eating.
 *
 * This function waits for each philosopher to signal that they are "full"
 * by waiting on the `full_sem` semaphore `philo_n` times. Once all
 * philosophers have signaled, it posts to the `stop_sem` semaphore
 * `philo_n` times to notify all waiting processes or threads that the
 * simulation can stop.
 *
 * @param args Pointer to a `t_args` structure containing simulation
 *             parameters, including the number of philosophers
 *             (`philo_n`), and the semaphores (`full_sem` and
 *             `stop_sem`).
 * @return Always returns NULL.
 */
void				*full_monitor(void *args);

//////////////////////////////// UTILS - MISC /////////////////////////////////

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
 * @brief Creates or opens a numbered POSIX semaphore with a unique name.
 *
 * This function generates a semaphore name by concatenating the given base
 * name with the string representation of the provided id. It then attempts
 * to open (or create) the semaphore with the specified initial value. The
 * semaphore is unlinked immediately after creation to ensure it is removed
 * when no longer in use.
 *
 * @param name The base name for the semaphore.
 * @param id The unique identifier to append to the base name.
 * @param value The initial value for the semaphore if it is created.
 * @return A pointer to the opened semaphore, or NULL on failure.
 */
sem_t				*get_sem_numbered(char *name, unsigned int id, int value,
						int unlink);

/**
 * @brief Gets the current time in milliseconds.
 *
 * This function retrieves the current system time using gettimeofday,
 * and returns the time in milliseconds since the Unix epoch.
 *
 * @return The current time in milliseconds as a long integer.
 */
unsigned int		get_time_ms(void);

/**
 * @brief Initializes the arguments structure with values from command-line
 *        arguments.
 *
 * This function sets up the fields of the t_args structure using the provided
 * command-line arguments. It initializes semaphore pointers to NULL, parses
 * integer values from argv, sets the epoch to the current time in
 * milliseconds, and calls set_sems() to initialize semaphores.
 *
 * @param args Pointer to the t_args structure to be initialized.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @return int Returns the result of set_sems(args).
 */
int					set_args(t_args *args, int argc, char *argv[]);

/**
 * @brief Sleeps for a specified duration in milliseconds, periodically
 *        checking a stop condition.
 *
 * This function sleeps for the given number of milliseconds, but wakes up
 * in small intervals (up to 10 ms) to check if a stop condition has been
 * triggered for the given philosopher. If the stop condition is met, the
 * function returns early.
 *
 * @param sleep The total sleep duration in milliseconds.
 * @param philo Pointer to the philosopher structure, used to check the
 *              stop condition.
 */
void				usleep_check(unsigned int sleep, t_philo *philo);

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
 * Sets the first n bytes of the memory pointed to by s to zero.
 *
 * @param s Pointer to the memory to be zeroed.
 * @param n Number of bytes to be zeroed.
 */
void				ft_bzero(void *s, size_t n);

/**
 * @brief Allocates memory for an array of elements and initializes them to 0.
 *
 * This function allocates memory for an array of `nmemb` elements,
 * each of `size` bytes, and initializes all the allocated memory to 0.
 * The total size of the allocated memory is calculated as `nmemb * size`.
 *
 * @param nmemb The number of elements to allocate memory for.
 * @param size The size of each element in bytes.
 * @return On success, a pointer to the allocated memory is returned.
 *         If either `nmemb` or `size` is 0, or if the multiplication of
 *         `nmemb` and `size` exceeds `INT_MAX`, then`NULL` is returned.
 *
 * @note If memory allocation fails, errno is set to ENOMEM.
 */
void				*ft_calloc(size_t nmemb, size_t size);

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

/**
 * @brief Copies a block of memory from a source address to a destination
 * address.
 *
 * This function copies the values of `n` bytes from the memory area pointed
 * to by `src` to the memory area pointed to by `dest`. The memory areas must
 * not overlap.
 *
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to be copied.
 * @return Pointer to the destination memory area (`dest`).
 */
void				*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Duplicates a string.
 *
 * This function allocates sufficient memory for a copy of the string s,
 * does the copy, and returns a pointer to it. The memory allocated for the
 * new string is obtained with malloc, and can be freed with free.
 *
 * @param s The string to duplicate.
 * @return A pointer to the duplicated string, or NULL if insufficient memory
 *         was available.
 */
char				*ft_strdup(const char *s);

/**
 * @brief Concatenates two strings into a new string.
 *
 * This function takes two null-terminated strings, `s1` and `s2`, and
 * concatenates them into a newly allocated string. The new string is
 * dynamically allocated and must be freed by the caller.
 *
 * @param s1 The first string to concatenate.
 * @param s2 The second string to concatenate.
 * @return A pointer to the newly allocated string containing the
 * concatenated result of `s1` and `s2`, or NULL if memory allocation fails.
 */
char				*ft_strjoin(char const *s1, char const *s2);

/**
 * Appends the string pointed to by `src` to the end of the string pointed to
 * by `dst`. It will append at most `size - strlen(dst) - 1` characters,
 * null-terminating the result.
 *
 * @param dst The destination string.
 * @param src The source string.
 * @param size The size of the destination buffer.
 * @return The total length of the string that would have been created if
 *         `size` was large enough. If the return value is greater than or
 *         equal to `size`, truncation occurred.
 */
size_t				ft_strlcat(char *dst, const char *src, size_t size);

/**
 * Calculates the length of a null-terminated string.
 *
 * @param str The string to calculate the length of.
 * @return The length of the string.
 */
size_t				ft_strlen(const char *str);

/**
 * @brief Converts an unsigned integer to a null-terminated string.
 *
 * This function takes an unsigned integer and converts it to a string
 * representation. The resulting string is dynamically allocated and
 * must be freed by the caller.
 *
 * @param n The unsigned integer to convert.
 * @return A pointer to the newly allocated string representing the number,
 *         or NULL if memory allocation fails.
 */
char				*ft_uitoa(unsigned int n);

////////////////////////// UTILS - PHILO LIST HELPERS //////////////////////////

/**
 * @brief Creates and initializes a new philosopher structure.
 *
 * Allocates memory for a new t_philo instance, sets its ID, initializes
 * the number of times eaten to zero, records the current timestamp as the
 * last meal time, and sets semaphore pointers and local stop flag to their
 * initial states. Associates the philosopher with the provided arguments.
 *
 * @param id   The unique identifier for the philosopher.
 * @param args Pointer to the shared arguments structure.
 * @return     Pointer to the newly created t_philo structure, or NULL on
 *             failure.
 */
t_philo				*create_philo(unsigned int id, t_args *args);

/**
 * @brief Cleans up resources associated with a philosopher instance.
 *
 * This function closes all semaphores associated with the given philosopher,
 * including argument semaphores, last meal semaphore, local stop semaphore,
 * and death monitor end semaphore, if they are valid and open. It then frees
 * the memory allocated for the philosopher structure.
 *
 * @param philo Pointer to the philosopher structure to be cleaned up.
 */
void				clean_philos(t_philo *philo);

/**
 * @brief Closes all open semaphores associated with the given arguments.
 *
 * This function checks each semaphore pointer in the provided t_args structure.
 * If a semaphore is valid (not NULL and not SEM_FAILED), it is closed using
 * sem_close. The full_sem semaphore is only closed if n_eat is greater than 0.
 *
 * @param args Pointer to the t_args structure containing semaphore handles.
 */
void				close_args_sems(t_args *args);

//////////////////////////// UTILS - SEM OPERATIOS /////////////////////////////

/**
 * @brief Safely performs a wait (decrement) operation on a semaphore.
 *
 * This function attempts to decrement (lock) the semaphore pointed to by `sem`.
 * If the semaphore pointer is NULL or if the `sem_wait` operation fails,
 * an error message is printed and the function returns 1 to indicate failure.
 * On success, returns 0.
 *
 * @param sem Pointer to the semaphore to wait on.
 * @return int 0 on success, 1 on failure.
 */
int					safe_sem_wait(sem_t *sem);

/**
 * @brief Safely posts (increments) a semaphore.
 *
 * This function attempts to increment (post) the given semaphore.
 * If the semaphore pointer is not NULL, it calls sem_post on it.
 * If sem_post fails, an error message is printed and the function returns 1.
 * Otherwise, it returns 0 on success.
 *
 * @param sem Pointer to the semaphore to be incremented.
 * @return int Returns 0 on success, 1 if sem_post fails.
 */
int					safe_sem_post(sem_t *sem);

/**
 * @brief Safely prints a string using a semaphore to ensure exclusive access.
 *
 * This function waits on the provided semaphore before printing the given
 * string, ensuring that only one process/thread can print at a time. After
 * printing, it posts to the semaphore to release it. If waiting or posting to
 * the semaphore fails, the function returns 1 to indicate an error.
 *
 * @param string The string to be printed.
 * @param args Pointer to a t_args structure containing the printf semaphore.
 * @return int Returns 0 on success, or 1 if a semaphore operation fails.
 */
int					safe_single_printf(char *string, t_args *args);

/**
 * @brief Safely prints a log message with synchronization using a semaphore.
 *
 * This function prints a formatted log message to the standard output,
 * ensuring that only one process/thread prints at a time by using a
 * semaphore. It also checks if the philosopher has stopped before and
 * after acquiring the semaphore to avoid printing unnecessary messages.
 *
 * @param string The format string to print (should include placeholders
 *               for time and id).
 * @param id The identifier to be printed in the log message.
 * @param args Pointer to the shared arguments structure containing the
 *             semaphore and epoch.
 * @param philo Pointer to the philosopher structure, used to check the
 *              stop condition.
 */
void				safe_log_printf(char *string, unsigned int id, t_args *args,
						t_philo *philo);
/**
 * @brief Safely retrieves the last meal timestamp of a philosopher.
 *
 * This function acquires a semaphore to ensure exclusive access to the
 * philosopher's last meal timestamp, copies its value to the provided pointer,
 * and then releases the semaphore. This prevents race conditions when multiple
 * processes or threads may access or modify the timestamp concurrently.
 *
 * @param philo Pointer to the philosopher structure whose last meal timestamp
 *              is to be retrieved.
 * @param last_meal Pointer to a int where the retrieved timestamp will be
 *                  stored.
 */
void				get_last_meal(t_philo *philo, unsigned int *last_meal);

/**
 * @brief Safely sets the last meal timestamp for a philosopher.
 *
 * This function updates the last_meal_timestamp field of the given
 * philosopher structure in a thread-safe manner by using a semaphore
 * to protect the critical section.
 *
 * @param philo Pointer to the philosopher structure whose last meal
 * timestamp is to be set.
 * @param last_meal The new timestamp value to set as the last meal time.
 */
void				set_last_meal(t_philo *philo, unsigned int last_meal);

/**
 * @brief Safely retrieves the value of the local_stop flag for a philosopher.
 *
 * This function acquires a semaphore to ensure thread-safe access to the
 * local_stop variable of the given philosopher. It stores the value of
 * philo->local_stop into the provided local_stop pointer, then releases
 * the semaphore.
 *
 * @param philo Pointer to the philosopher structure whose local_stop value is
 *              to be read.
 * @param local_stop Pointer to an unsigned int where the local_stop value will
 *                   be stored.
 */
void				get_local_stop(t_philo *philo, unsigned int *local_stop);

/**
 * @brief Sets the local stop flag for a philosopher in a thread-safe manner.
 *
 * This function acquires the semaphore associated with the philosopher's
 * local stop flag, updates the flag with the provided value, and then
 * releases the semaphore. This ensures that the update operation is
 * performed atomically and prevents race conditions in concurrent
 * environments.
 *
 * @param philo Pointer to the philosopher structure whose local stop flag
 * is to be set.
 * @param local_stop The value to set for the local stop flag.
 */
void				set_local_stop(t_philo *philo, unsigned int local_stop);

/**
 * @brief Waits on the stop semaphore for each philosopher.
 *
 * This function iterates through the number of philosophers and performs a wait
 * operation on the stop semaphore for each one. It is typically used to ensure
 * that all philosopher processes have reached a certain stopping point before
 * proceeding.
 *
 * @param args Pointer to the arguments structure containing the number of
 * philosophers and the stop semaphore.
 */
void				set_stop_sem(t_args *args);

#endif
