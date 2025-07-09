/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:55:05 by pablo             #+#    #+#             */
/*   Updated: 2025/07/09 13:55:16 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

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
	if (dead)
	{
		safe_log_printf("%10u " BOLD MAGENTA "%u" RESET RED " has died"
			RESET "\n", philo->id, philo->args);
		set_simulation_running(philo->args, 0);
	}
	return (dead);
}

/**
 * @brief Safely retrieves the last meal timestamp of a philosopher.
 *
 * This function locks the philosopher's internal mutex to safely read
 * the last meal timestamp and stores it in the provided pointer.
 * It ensures thread-safe access to the philosopher's data.
 *
 * @param philo Pointer to the philosopher structure.
 * @param last_meal Pointer to a long where the last meal timestamp will
 *                  be stored.
 * @return int Returns 0 on success, or 1 if a mutex lock/unlock operation
 *         fails.
 */
static int	get_last_meal(t_philo *philo, long *last_meal)
{
	if (safe_mutex_lock(&philo->internal_mutex, philo->args))
		return (1);
	*last_meal = philo->last_meal_timestamp;
	if (safe_mutex_unlock(&philo->internal_mutex, philo->args))
		return (1);
	return (0);
}

int	check_philo_death(t_philo *philo)
{
	long	current_time;
	long	last_meal;

	current_time = get_time_ms();
	if (get_last_meal(philo, &last_meal))
		return (1);
	return (check_death_conditions(philo, current_time, last_meal));
}
