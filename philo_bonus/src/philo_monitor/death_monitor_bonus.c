/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:08:13 by pablo             #+#    #+#             */
/*   Updated: 2025/07/02 13:08:12 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * @brief Monitors the death status of a philosopher in a concurrent
 * environment.
 *
 * This function runs in a separate thread or process and continuously
 * checks whether the given philosopher has died by calling
 * `check_philo_death()`. It uses semaphores to safely access shared
 * state. When a philosopher is detected as dead, it sets the stop
 * semaphore and signals the death semaphore for all philosophers to
 * notify them of the event.
 *
 * @param args Pointer to a t_philo structure representing the philosopher
 *             to monitor.
 * @return Always returns NULL.
 */
static void	*death_monitor(void *args)
{
	t_philo			*philo;
	int				is_dead;
	unsigned int	counter;

	philo = (t_philo *)args;
	is_dead = 0;
	counter = 0;
	while (!is_dead)
	{
		safe_sem_wait(philo->args->stop_sem);
		is_dead = check_philo_death(philo);
		safe_sem_post(philo->args->stop_sem);
	}
	while (counter < philo->args->philo_n)
	{
		safe_sem_post(philo->args->death_sem);
		++counter;
	}
	set_stop_sem(philo->args);
	return (NULL);
}

/**
 * @brief Monitors the death semaphore and terminates the process when
 * triggered.
 *
 * This function is intended to be run as a separate thread or process.
 * It waits on the death semaphore (`death_sem`) in the philosopher's args.
 * When the semaphore is posted (indicating a philosopher's death or stop),
 * the function calls `exit(0)` to terminate the process.
 *
 * @param args Pointer to a `t_philo` structure with philosopher data and
 * semaphores.
 * @return Always returns NULL, but the process will exit before returning.
 */
static void	*death_stop_monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	sem_wait(philo->args->death_sem);
	// Only clean local resources in child process
	clean_philos(philo);
	exit(0);
	return (NULL);
}

int	start_death_monitors(t_philo *philo)
{
	pthread_t	death_monitor_id;
	pthread_t	death_stop_monitor_id;

	if (pthread_create(&death_monitor_id, NULL, death_monitor, philo) != 0)
	{
		printf(RED "Error: Failed to create death monitor thread\n" RESET);
		return (1);
	}
	if (pthread_create(&death_stop_monitor_id, NULL, death_stop_monitor,
			philo) != 0)
	{
		printf(RED "Error: Failed to create death stop monitor thread\n" RESET);
		return (1);
	}
	pthread_detach(death_monitor_id);
	pthread_detach(death_stop_monitor_id);
	return (0);
}
