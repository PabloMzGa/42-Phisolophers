/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:23:38 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/25 18:00:53 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Sleeps for a specified amount of time in ms, checking periodically
 *        if the simulation is still running.
 *
 * This function divides the total sleep time into smaller intervals
 * (MICROSLEEP_MS) and after each interval, checks if the simulation
 * should continue running by calling get_simulation_running(args).
 * If the simulation is no longer running, the function returns early.
 *
 * @param sleep The total time to sleep in milliseconds.
 * @param args Pointer to the simulation arguments structure, used to check
 *             simulation state.
 */
void usleep_check(unsigned int sleep, t_args *args)
{
	unsigned int sleep_counter;
	unsigned int next_microsleep;

	sleep_counter = 0;
	while (sleep_counter < sleep)
	{
		if (!get_simulation_running(args))
			return;
		if (sleep - sleep_counter < MICROSLEEP_MS)
			next_microsleep = sleep - sleep_counter;
		else
			next_microsleep = MICROSLEEP_MS;
		usleep(next_microsleep * 1000);
		sleep_counter += next_microsleep;
	}
}
