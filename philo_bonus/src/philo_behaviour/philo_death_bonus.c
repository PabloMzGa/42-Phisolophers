/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:55:05 by pablo             #+#    #+#             */
/*   Updated: 2025/07/03 14:02:51 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * @brief Checks if a philosopher has died based on the current time and last
 * meal time.
 *
 * This function determines whether the philosopher has died by checking two
 * conditions:
 * 1. If the current time is less than the last meal time (possible time
 *    inconsistency).
 * 2. If the elapsed time since the last meal exceeds the allowed time to die.
 *
 * If either condition is met, the function prints a death message, sets the
 * simulation running flag to 0 (stopping the simulation), and returns 1 to
 * indicate death.
 *
 * @param philo         Pointer to the philosopher structure.
 * @param current_time  The current timestamp in milliseconds.
 * @param last_meal     The timestamp of the philosopher's last meal in ms.
 * @return int          1 if the philosopher has died, 0 otherwise.
 */
static int	check_death_conditions(t_philo *philo, long current_time,
		long last_meal)
{
	long	elapsed;
	int		dead;

	dead = 0;
	if (current_time < last_meal)
		dead = 1;
	elapsed = current_time - last_meal;
	if (elapsed > philo->args->time_die)
		dead = 1;
	/**/
	if (dead)
	{
		safe_log_printf("%10u " BOLD MAGENTA
			"%u" RESET RED " has died" RESET "\n", philo->id, philo->args, philo);
		set_local_stop(philo, 1);
	}
	return (dead);
}

int	check_philo_death(t_philo *philo)
{
	long			current_time;
	unsigned int	last_meal;

	current_time = get_time_ms();
	if (get_last_meal(philo, &last_meal))
		return (1);
	return (check_death_conditions(philo, current_time, last_meal));
}
