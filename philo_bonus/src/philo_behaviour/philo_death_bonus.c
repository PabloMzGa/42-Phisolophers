/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:55:05 by pablo             #+#    #+#             */
/*   Updated: 2025/07/11 13:13:27 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * @brief Checks if a philosopher has died based on the elapsed time since
 *        their last meal.
 *
 * This function calculates the time elapsed since the philosopher's last
 * meal and compares it to the allowed time to die (`time_die`). If the
 * elapsed time exceeds `time_die`, the philosopher is considered dead.
 * In that case, a log message is printed and the local stop flag is set.
 *
 * @param philo Pointer to the philosopher structure.
 * @param current_time The current timestamp.
 * @param last_meal The timestamp of the philosopher's last meal.
 * @return 1 if the philosopher has died, 0 otherwise.
 */
static int	check_death_conditions(t_philo *philo, long current_time,
		long last_meal)
{
	long	elapsed;
	int		dead;

	dead = 0;
	elapsed = current_time - last_meal;
	if (elapsed < 0)
		return (0);
	if (elapsed > philo->args->time_die)
		dead = 1;
	if (dead)
	{
		safe_log_printf("%10u " BOLD MAGENTA
			"%u" RESET RED " has died" RESET "\n", philo->id, philo->args,
			philo);
		set_local_stop(philo, 1);
	}
	return (dead);
}

int	check_philo_death(t_philo *philo)
{
	long			current_time;
	unsigned int	last_meal_uint;
	long			last_meal;

	current_time = get_time_ms();
	get_last_meal(philo, &last_meal_uint);
	last_meal = (long)last_meal_uint;
	return (check_death_conditions(philo, current_time, last_meal));
}
