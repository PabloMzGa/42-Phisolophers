/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_monitor_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:08:13 by pablo             #+#    #+#             */
/*   Updated: 2025/07/02 14:14:51 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

static void	kill_philosophers(t_philo *philo)
{
	t_philo	*current_philo;

	current_philo = philo;
	while (current_philo->next)
	{
		kill(current_philo->pid, SIGTERM);
		current_philo = current_philo->next;
	}
	kill(current_philo->pid, SIGTERM);
	current_philo = current_philo->next;
	printf(BOLD GREEN "All philosophers have eaten the target "
						"number of times, ending simulation" RESET "\n");
}

/**
 * @brief Monitors the "full" semaphore for a philosopher and terminates the
 * process when triggered.
 *
 * This function is intended to be run as a thread or process. It waits on the
 * `full_sem` semaphore associated with the philosopher's arguments. When the
 * semaphore is posted (indicating the philosopher is "full"), it performs
 * cleanup for the philosopher and then exits the process.
 *
 * @param args Pointer to a t_philo structure representing the philosopher.
 * @return Always returns NULL, but the process will exit before reaching this
 * point.
 */
static void	*full_stop_monitor(void *args)
{
	t_philo			*philo;
	unsigned int	i;

	philo = (t_philo *)args;
	i = 0;
	printf("Iniciando monitor de saciedad \n");
	while (i < philo->args->philo_n)
	{
		sem_wait(philo->args->full_sem);
		++i;
	}
	safe_sem_wait(philo->args->stop_sem);
	kill_philosophers(philo);
	return (NULL);
}

int	start_full_monitor(t_philo *philo)
{
	pthread_t	full_monitor_id;

	if (pthread_create(&full_monitor_id, NULL, full_stop_monitor, philo) != 0)
	{
		printf(RED "Error: Failed to create death monitor thread\n" RESET);
		return (1);
	}
	pthread_detach(full_monitor_id);
	return (0);
}
