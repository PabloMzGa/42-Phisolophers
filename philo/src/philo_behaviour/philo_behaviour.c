/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:22:16 by pablo             #+#    #+#             */
/*   Updated: 2025/06/25 17:59:40 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

/**
 * @brief Main loop for philosopher behavior.
 *
 * This function represents the main behavior loop for a philosopher.
 * While the simulation is running, the philosopher will attempt to eat,
 * check if they have eaten enough times (and update their status to FULL
 * if so), and then proceed to sleep and think. The loop continues as long as
 * the simulation is active.
 *
 * @param philo Pointer to the philosopher structure.
 */
static void	behaviour_loop(t_philo *philo)
{
	int	still_running;

	still_running = get_simulation_running(philo->args);
	while (still_running)
	{
		if (philo->next)
		{
			philosopher_eat(philo);
			if (philo->args->n_eat != 0 && philo->n_eat >=
				philo->args->n_eat && get_philo_status(philo) != FULL)
				set_philo_status(philo, FULL);
			philosopher_sleep_think(philo);
		}
		still_running = get_simulation_running(philo->args);
	}
}

void	*philosopher_behaviour(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 != 0)
		usleep_check((philo->args->time_die / 20), philo->args);
	behaviour_loop(philo);
	return (NULL);
}
