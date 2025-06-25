/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death_monitor_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:08:13 by pablo             #+#    #+#             */
/*   Updated: 2025/06/25 19:02:46 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * @brief Monitors the death status of a philosopher in a separate thread.
 *
 * This function continuously checks if the philosopher has died by calling
 * check_philo_death(). Once the philosopher is detected as dead, it posts
 * to the death semaphore for each philosopher to signal the event.
 *
 * @param args Pointer to the philosopher structure (t_philo *).
 * @return NULL Always returns NULL.
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
		is_dead = check_philo_death(philo);
	while (counter < philo->args->philo_n)
	{
		sem_post(philo->args->death_sem);
		++counter;
	}
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
	exit(0);
	return (NULL);
}

int	start_death_monitors(t_philo *philos)
{
	if (pthread_create(NULL, NULL, death_monitor, philos) != 0)
	{
		printf(RED "Error: Failed to create death monitor thread\n" RESET);
		return (1);
	}
	if (pthread_create(NULL, NULL, death_stop_monitor, philos) != 0)
	{
		printf(RED "Error: Failed to create death stop monitor thread\n" RESET);
		return (1);
	}
	return (0);
}
