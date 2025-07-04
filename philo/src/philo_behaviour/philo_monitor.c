/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:08:13 by pablo             #+#    #+#             */
/*   Updated: 2025/07/04 13:11:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

/**
 * @brief Determines whether the philosopher simulation should continue.
 *
 * Checks if the simulation should keep running based on three conditions:
 * - Whether all philosophers are full (`all_full`).
 * - Whether any philosopher has died (`someone_died`).
 * - Whether the simulation is marked as running (`simulation_running`),
 *   which is accessed in a thread-safe manner.
 *
 * The function locks the simulation mutex to safely read the
 * `simulation_running` flag, then unlocks it before returning the result.
 *
 * @param philos Pointer to a philosopher structure, used to access shared
 *        simulation arguments.
 * @param all_full Non-zero if all philosophers have eaten enough; zero
 *        otherwise.
 * @param someone_died Non-zero if any philosopher has died; zero otherwise.
 * @return int Returns 1 if the simulation should continue, 0 otherwise.
 */
static int	should_continue(t_philo *philos, int all_full, int someone_died)
{
	int	running;

	running = get_simulation_running(philos->args);
	return (!all_full && !someone_died && running);
}

/**
 * @brief Checks the status of all philosophers to determine if they are all
 *        full and if any philosopher has died.
 *
 * This function iterates through the list of philosophers, locking each
 * one's internal mutex to safely check their status. It sets the value
 * pointed to by `all_full` to 1 if all philosophers have reached the FULL
 * status, or to 0 if at least one has not. If a philosopher is not full,
 * it checks if that philosopher has died using `check_philo_death`. The
 * function returns 1 if a mutex lock/unlock fails or if a philosopher has
 * died, and 0 otherwise.
 *
 * @param philos   Pointer to the first philosopher in the list.
 * @param all_full Pointer to an integer that will be set to 1 if all
 *                 philosophers are full, or 0 otherwise.
 * @return         1 if a philosopher has died or a mutex operation fails,
 *                 0 otherwise.
 */
static int	check_all_philosophers(t_philo *philos, int *all_full)
{
	t_philo	*current_philo;
	unsigned int	i;
	int		someone_died;
	int		status;

	current_philo = philos;
	i = 0;
	*all_full = 1;
	someone_died = 0;
	while (i < philos->args->philo_n && !someone_died)
	{
		status = get_philo_status(philos);
		if (status == -1)
			return (1);
		if (status != FULL)
			*all_full = 0;
		if (!(*all_full))
			someone_died = check_philo_death(current_philo);
		current_philo = current_philo->next;
		i++;
	}
	return (someone_died);
}

/**
 * @brief Monitor routine for philosopher simulation.
 *
 * This function is intended to be run as a separate thread. It continuously
 * monitors the state of all philosophers in the simulation, checking if any
 * philosopher has died or if all philosophers have eaten the required number
 * of times.
 *
 * The routine loops while the simulation should continue, as determined by
 * the `should_continue` function. In each iteration, it checks the status of
 * all philosophers using `check_all_philosophers`, which updates the
 * `all_full` and `someone_died` flags. If no philosopher has died and not all
 * are full, the thread sleeps briefly to reduce CPU usage.
 *
 * When the monitoring detects that all philosophers are full and none have
 * died, it safely locks the simulation mutex, sets the simulation running
 * flag to 0 (ending the simulation), unlocks the mutex, and prints a message
 * indicating successful completion.
 *
 * @param args Pointer to the first philosopher structure (t_philo *).
 * @return NULL on completion.
 */
static void	*monitor_routine(void *args)
{
	t_philo	*philos;
	int		all_full;
	int		someone_died;

	philos = (t_philo *)args;
	all_full = 0;
	someone_died = 0;
	while (should_continue(philos, all_full, someone_died))
	{
		someone_died = check_all_philosophers(philos, &all_full);
		if (!someone_died && !all_full)
			usleep(1000);
	}
	if (all_full && !someone_died)
	{
		set_simulation_running(philos->args, 0);
		safe_single_printf(BOLD GREEN "All philosophers have eaten the target "
			"number of times, ending simulation\n" RESET, philos->args);
	}
	return (NULL);
}

pthread_t	start_monitor(t_philo *philos)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor_routine, philos) != 0)
	{
		printf(RED "Error: Failed to create monitor thread\n" RESET);
		if (safe_mutex_lock(&philos->args->simulation_mutex, philos->args))
			return (0);
		set_simulation_running(philos->args, 0);
		safe_mutex_unlock(&philos->args->simulation_mutex, philos->args);
		return (0);
	}
	return (monitor_thread);
}
