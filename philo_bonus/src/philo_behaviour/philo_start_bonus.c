/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:26:47 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/07 22:31:35 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * @brief Starts and manages the philosopher's behaviour and monitoring threads.
 *
 * This function creates three threads for a philosopher:
 *
 * - The main behaviour loop thread (`philo_behaviour_loop`)
 *
 * - The death monitor thread (`death_monitor`)
 *
 * - The stop monitor thread (`stop_monitor`)
 *
 * The stop and death monitor threads are detached, while the behaviour thread
 * is joined before returning. If any thread fails to be created, an error
 * message is printed and the function returns 1.
 *
 * @param philo Pointer to the philosopher structure.
 * @return int Returns 0 on success, 1 on failure or if `philo` is NULL.
 */
static int	start_and_join_behaviours(t_philo *philo)
{
	pthread_t	behaviour_thread_id;
	pthread_t	death_monitor_id;
	pthread_t	stop_monitor_id;

	if (!philo)
		return (1);
	if (pthread_create(&behaviour_thread_id, NULL, philo_behaviour_loop,
			philo) != 0)
		return (printf(RED "Error: Failed to create behaviour thread\n" RESET),
			1);
	if (pthread_create(&death_monitor_id, NULL, death_monitor, philo) != 0)
		return (printf(RED "Error: Failed to create death monitor thread\n"
			RESET), 1);
	if (pthread_create(&stop_monitor_id, NULL, stop_monitor, philo) != 0)
		return (printf(RED "Error: Failed to create death stop monitor thread\n"
			RESET), 1);
	pthread_detach(stop_monitor_id);
	pthread_detach(death_monitor_id);
	pthread_join(behaviour_thread_id, NULL);
	return (0);
}

/**
 * @brief Opens and initializes the semaphores required for a philosopher
 *        instance.
 *
 * This function creates or opens three semaphores for the given philosopher:
 *
 * - last_meal_sem: Used to synchronize access to the philosopher's last meal
 *   time.
 *
 * - local_stop_sem: Used to signal a local stop condition for the philosopher.
 *
 * - death_monitor_end_sem: Used to signal the end of the death monitoring
 *   process.
 *
 * Each semaphore is uniquely named using the philosopher's id to avoid
 * conflicts. If any semaphore fails to open or initialize, the function
 * cleans up any previously opened semaphores and returns NULL.
 *
 * @param philo Pointer to the philosopher structure for which semaphores are
 *        to be opened.
 * @return Pointer to the philosopher structure with initialized semaphores,
 *         or NULL on failure.
 */
static t_philo	*open_philo_semaphores(t_philo *philo)
{
	philo->last_meal_sem = get_sem_numbered("/last_meal_sem", philo->id, 1, 1);
	if (philo->last_meal_sem == NULL)
		return (clean_philos(philo), NULL);
	philo->local_stop_sem = get_sem_numbered("/local_stop_sem", philo->id, 1,
			1);
	if (philo->local_stop_sem == NULL)
		return (clean_philos(philo), NULL);
	philo->death_monitor_end_sem = get_sem_numbered("/death_monitor_end_sem",
			philo->id, 0, 1);
	if (philo->death_monitor_end_sem == NULL)
		return (clean_philos(philo), NULL);
	return (philo);
}

/**
 * @brief Signals all philosopher processes to stop by posting to the stop
 * semaphore.
 *
 * This function iterates over the number of philosophers and posts to the
 * stop semaphore (`stop_sem`) for each philosopher. This is typically used
 * in emergency situations to ensure all philosopher processes are notified
 * to stop their execution.
 *
 * @param args Pointer to the arguments structure containing the number of
 *             philosophers (`philo_n`) and the stop semaphore (`stop_sem`).
 */
static void	emergency_stop(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->philo_n)
	{
		safe_sem_post(args->stop_sem);
		++i;
	}
}

/**
 * @brief Creates a new process for a philosopher and starts its behaviour.
 *
 * This function forks the current process to create a new philosopher process.
 * In the child process, it opens the necessary semaphores and starts the
 * philosopher's behaviour routines. If an error occurs during the behaviour
 * startup, it triggers an emergency stop if more than one philosopher exists,
 * frees the philosopher structure, and returns NULL. In the parent process,
 * if fork fails, it also triggers an emergency stop if needed, frees the
 * philosopher structure, and returns NULL. Otherwise, it returns the PID of
 * the newly created child process.
 *
 * @param tmp_philo Pointer to the philosopher structure to be used by the new
 *        process.
 * @param counter The number of philosophers (used to determine if emergency
 *        stop is needed).
 * @return In the parent process, returns the PID of the child process on
 *         success, or NULL on failure. In the child process, returns
 *         tmp_philo on success, or NULL on failure.
 */
static pid_t	philo_fork(t_philo *tmp_philo, unsigned int counter)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (start_and_join_behaviours(open_philo_semaphores(tmp_philo)))
		{
			if (counter > 1)
				emergency_stop(tmp_philo->args);
			free(tmp_philo);
			return (-1);
		}
		return (pid);
	}
	if (pid == -1)
	{
		if (counter > 1)
			emergency_stop(tmp_philo->args);
		free(tmp_philo);
		return (-1);
	}
	return (pid);
}

t_philo	*philo_start(t_args *args)
{
	unsigned int	counter;
	t_philo			*tmp_philo;

	counter = 1;
	while (counter <= args->philo_n)
	{
		tmp_philo = create_philo(counter, args);
		if (!tmp_philo)
		{
			if (counter > 1)
				emergency_stop(args);
			return (NULL);
		}
		tmp_philo->pid = philo_fork(tmp_philo, counter);
		if (tmp_philo->pid == -1)
			return (NULL);
		free(tmp_philo);
		++counter;
	}
	return (NULL);
}
