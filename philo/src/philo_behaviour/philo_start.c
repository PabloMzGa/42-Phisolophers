/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:38:09 by pablo             #+#    #+#             */
/*   Updated: 2025/07/08 14:05:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

/**
 * @brief Waits for all philosopher threads to finish execution.
 *
 * Iterates through the linked list of philosopher structures and joins each
 * philosopher's thread, ensuring that the main thread waits until all
 * philosopher threads have completed. The number of philosophers is determined
 * by the 'philo_n' field in the 'args' member of the first philosopher.
 *
 * @param philos Pointer to the first philosopher in the linked list.
 */
void	wait_philo_end(t_philo *philos)
{
	t_philo			*current_philo;
	unsigned int	i;

	current_philo = philos;
	i = 0;
	while (i < philos->args->philo_n)
	{
		pthread_join(current_philo->thread, NULL);
		current_philo = current_philo->next;
		i++;
	}
}

/**
 * @brief Starts the main loop to create philosopher threads.
 *
 * Iterates through the list of philosophers and creates a thread for each one,
 * executing the philosopher_behaviour function. If thread creation fails for
 * any philosopher, the simulation is stopped, an error message is printed,
 * and all philosopher threads are waited for to finish before returning an
 * error code.
 *
 * @param philos Pointer to the first philosopher in the linked list.
 * @return int Returns 0 on success, or 1 if thread creation fails.
 */
static int	start_loop(t_philo *philos)
{
	t_philo			*current_philo;
	unsigned int	i;

	current_philo = philos;
	i = 0;
	while (i < philos->args->philo_n)
	{
		if (pthread_create(&(current_philo->thread), NULL,
				philosopher_behaviour, (void *)current_philo))
		{
			set_simulation_running(philos->args, 0);
			printf(RED "Error: Failed to create thread for philosopher %u\n"
				RESET, current_philo->id);
			wait_philo_end(philos);
			return (1);
		}
		current_philo = current_philo->next;
		i++;
	}
	return (0);
}

void	start_philosophers_behaviour(t_philo *philos)
{
	pthread_t	monitor_thread;

	if (start_loop(philos))
		return ;
	monitor_thread = start_monitor(philos);
	if (monitor_thread != 0)
		pthread_join(monitor_thread, NULL);
	wait_philo_end(philos);
}
