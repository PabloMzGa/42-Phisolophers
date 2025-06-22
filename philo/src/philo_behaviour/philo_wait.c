/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:29:36 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 00:31:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

/**
 * @brief Joins all philosopher threads to ensure they have finished execution.
 *
 * Iterates through the linked list of philosopher structures and calls
 * pthread_join on each philosopher's thread. This function ensures that
 * the main thread waits for all philosopher threads to complete before
 * proceeding. The number of philosophers is determined by
 * philos->args->philo_n.
 *
 * @param philos Pointer to the first philosopher in the linked list.
 */
static void 	join_philos_threads(t_philo *philos)
{
	t_philo	*current_philo;
	size_t	i;

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
void	wait_philo_end(t_philo *philos)
{
	t_philo	*current_philo;
	size_t	i;
	int		philo_full;

	join_philos_threads(philos);
	i = 0;
	current_philo = philos;
	while (i < philos->args->philo_n)
	{
		philo_full = current_philo->status != FULL;
		current_philo = current_philo->next;
		i++;
	}
	if (!philo_full)
		printf(BOLD GREEN "All philiosophers have eaten the target number of "
			"times, ending simulation\n" RESET);
}
