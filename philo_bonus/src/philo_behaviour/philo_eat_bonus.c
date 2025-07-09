/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:11:04 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/09 16:07:33 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * @brief Handles the action of a philosopher picking up a fork.
 *
 * This function waits on the semaphore representing the forks,
 * checks if the philosopher should stop (using get_local_stop),
 * and if so, releases the semaphore and returns 1 to indicate
 * the action was not completed. Otherwise, it logs the fork pickup
 * event and returns 0 to indicate success.
 *
 * @param philo Pointer to the philosopher structure.
 * @return int 1 if the philosopher should stop, 0 otherwise.
 */
static int	handle_fork_pickup(t_philo *philo)
{
	unsigned int	local_stop;

	safe_sem_wait(philo->args->forks_sem);
	get_local_stop(philo, &local_stop);
	if (local_stop)
	{
		safe_sem_post(philo->args->forks_sem);
		return (1);
	}
	safe_log_printf("%10u " BOLD MAGENTA "%u" RESET GREEN " has taken a fork"
		RESET "\n", philo->id, philo->args, philo);
	return (0);
}

/**
 * @brief Handles the eating behavior of a philosopher.
 *
 * This function logs that the philosopher is eating, updates the last meal
 * time, makes the philosopher sleep for the eating duration, releases both
 * forks by posting to the semaphore twice, and increments the philosopher's
 * eat count.
 *
 * @param philo Pointer to the philosopher structure whose eating behavior is
 * being handled.
 */
static void	handle_eating(t_philo *philo)
{
	safe_log_printf("%10u " BOLD MAGENTA "%u" RESET YELLOW " is eating" RESET
		"\n", philo->id, philo->args, philo);
	set_last_meal(philo, get_time_ms());
	usleep_check(philo->args->time_eat * 1000, philo);
	safe_sem_post(philo->args->forks_sem);
	safe_sem_post(philo->args->forks_sem);
	philo->n_eat++;
}

int	philo_eat(t_philo *philo)
{
	unsigned int	local_stop;

	get_local_stop(philo, &local_stop);
	if (local_stop)
		return (1);
	safe_sem_wait(philo->args->grabbing_forks_sem);
	if (handle_fork_pickup(philo))
		return (safe_sem_post(philo->args->grabbing_forks_sem), 1);
	if (philo->args->philo_n == 1)
		return (safe_sem_post(philo->args->grabbing_forks_sem), 0);
	if (handle_fork_pickup(philo))
		return (safe_sem_post(philo->args->grabbing_forks_sem), 1);
	safe_sem_post(philo->args->grabbing_forks_sem);
	handle_eating(philo);
	return (0);
}
