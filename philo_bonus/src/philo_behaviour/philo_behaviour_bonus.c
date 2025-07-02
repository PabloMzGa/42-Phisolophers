/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:22:16 by pablo             #+#    #+#             */
/*   Updated: 2025/06/30 12:58:40 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"


/**
 * @brief Main behaviour loop for a philosopher.
 *
 * This function represents the core loop executed by each philosopher.
 * In each iteration, the philosopher performs the following actions:
 *
 *   1. Attempts to eat by calling philosopher_eat().
 *
 *   2. Checks if the philosopher has eaten the required number of times
 *      (if n_eat is not -1 and n_eat has been reached or exceeded).
 *      If so, sets the philosopher's status to FULL and signals this
 *      event by posting to the full_sem semaphore.
 *
 *   3. Proceeds to sleep and think by calling philosopher_sleep_think().
 *
 * The loop continues indefinitely. It's the monitor who will exit the process.
 *
 * @param philo Pointer to the philosopher structure containing state and
 *              arguments.
 */
static void	behaviour_loop(t_philo *philo)
{
	while (1)
	{
		philosopher_eat(philo);
		if (philo->status != FULL && philo->args->n_eat != 0
			&& philo->n_eat >= philo->args->n_eat)
		{
			philo->status = FULL;
			safe_sem_post(philo->args->full_sem);
		}
		philosopher_sleep_think(philo);
	}
}

/**
 * @brief Executes the main behaviour routine for a philosopher.
 *
 * This function introduces a slight delay for philosophers with odd IDs
 * to reduce contention when starting simultaneously. After the optional
 * delay, it enters the main behaviour loop for the philosopher.
 *
 * @param philo Pointer to the philosopher structure containing its state and
 *              arguments.
 */
void	philosopher_behaviour(t_philo *philo)
{
	start_death_monitors(philo);
	behaviour_loop(philo);
}
