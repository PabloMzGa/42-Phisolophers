/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:22:16 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 22:13:10 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

/**
 * @brief Main loop controlling the philosopher's behavior during the simulation.
 *
 * This function manages the actions of a philosopher, allowing them to eat,
 * sleep, and think as long as the simulation is running and the philosopher
 * has not reached the required number of meals (if specified).
 *
 * The loop continues while:
 *
 *   - The philosopher has not eaten the required number of times
 *     (or unlimited if n_eat == -1).
 *
 *   - The simulation is still running.
 *
 * Inside the loop:
 *
 *   - If the philosopher has a next neighbor, they attempt to eat.
 *
 *   - After eating, if the philosopher is still hungry and the simulation is
 *     running, they proceed to sleep and think.
 *
 *   - The running status of the simulation is updated at the end of each
 *     iteration.
 *
 * @param philo         Pointer to the philosopher structure.
 * @param still_running Initial flag indicating if the simulation is running.
 */
static void	behaviour_loop(t_philo *philo, int still_running)
{
	int	continue_eating;

	while ((philo->args->n_eat == -1 || philo->args->n_eat != philo->n_eat)
		&& still_running)
	{
		if (philo->next)
		{
			philosopher_eat(philo);
			continue_eating = (get_philo_status(philo) == HUNGRY
					&& get_simulation_running(philo->args));
			if (continue_eating)
				philosopher_sleep_think(philo);
		}
		still_running = get_simulation_running(philo->args);
	}
}

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
void	*philosopher_behaviour(void *args)
{
	t_philo	*philo;
	int		still_running;

	philo = (t_philo *)args;
	if (philo->id % 2 != 0)
		usleep((philo->args->time_die / 20) * 1000);
	still_running = get_simulation_running(philo->args);
	behaviour_loop(philo, still_running);
	if (philo->args->n_eat != -1 && philo->n_eat >= philo->args->n_eat)
		set_philo_status(philo, FULL);
	return (NULL);
}
