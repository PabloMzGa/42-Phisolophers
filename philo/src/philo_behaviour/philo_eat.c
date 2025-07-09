/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:53:12 by pablo             #+#    #+#             */
/*   Updated: 2025/07/09 13:52:07 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

/**
 * @brief Attempts to acquire the first fork (mutex).
 *
 * @param philo   Pointer to the philosopher structure.
 * @param f_mutex Pointer to the first mutex to lock.
 * @return        0 on success, 1 on failure or simulation stop.
 */
static int	acquire_first_fork(t_philo *philo, pthread_mutex_t *f_mutex)
{
	if (safe_mutex_lock(f_mutex, philo->args))
		return (1);
	if (check_stop(philo, f_mutex, NULL))
		return (1);
	if (safe_log_printf("%10u" BOLD MAGENTA " %u" RESET GREEN
			" has taken a fork\n" RESET, philo->id, philo->args))
		return (1);
	return (0);
}

/**
 * @brief Attempts to acquire the second fork (mutex).
 *
 * @param philo   Pointer to the philosopher structure.
 * @param f_mutex Pointer to the first mutex (already locked).
 * @param s_mutex Pointer to the second mutex to lock.
 * @return        0 on success, 1 on failure or simulation stop.
 */
static int	acquire_second_fork(t_philo *philo, pthread_mutex_t *f_mutex,
		pthread_mutex_t *s_mutex)
{
	if (safe_mutex_lock(s_mutex, philo->args))
	{
		safe_mutex_unlock(f_mutex, philo->args);
		return (1);
	}
	if (check_stop(philo, f_mutex, s_mutex))
		return (1);
	if (safe_log_printf("%10u" BOLD MAGENTA " %u" RESET GREEN
			" has taken a fork\n" RESET, philo->id, philo->args))
		return (1);
	return (0);
}

/**
 * @brief Performs the eating action and updates philosopher state.
 *
 * @param philo Pointer to the philosopher structure.
 */
static void	perform_eating(t_philo *philo)
{
	if (safe_log_printf("%10u" BOLD MAGENTA " %u" RESET YELLOW
			" is eating\n" RESET, philo->id,
			philo->args))
		return ;
	if (safe_mutex_lock(&philo->internal_mutex, philo->args))
		return ;
	philo->last_meal_timestamp = get_time_ms();
	if (safe_mutex_unlock(&philo->internal_mutex, philo->args))
		return ;
	usleep_check(philo->args->time_eat, philo->args);
	philo->n_eat++;
}

/**
 * @brief Releases both forks (mutexes) with error checking.
 *
 * @param philo   Pointer to the philosopher structure.
 * @param f_mutex Pointer to the first mutex to unlock.
 * @param s_mutex Pointer to the second mutex to unlock.
 */
static void	release_forks(t_philo *philo, pthread_mutex_t *f_mutex,
		pthread_mutex_t *s_mutex)
{
	safe_mutex_unlock(f_mutex, philo->args);
	safe_mutex_unlock(s_mutex, philo->args);
}

void	philosopher_eat(t_philo *philo)
{
	pthread_mutex_t	*f_mutex;
	pthread_mutex_t	*s_mutex;
	int				first_acquired;
	int				second_acquired;

	select_mutex(&f_mutex, &s_mutex, philo);
	first_acquired = 0;
	second_acquired = 0;
	if (get_simulation_running(philo->args)
		&& !acquire_first_fork(philo, f_mutex))
		first_acquired = 1;
	if (first_acquired && get_simulation_running(philo->args)
		&& !acquire_second_fork(philo, f_mutex, s_mutex))
		second_acquired = 1;
	if (first_acquired && second_acquired
		&& get_simulation_running(philo->args))
		perform_eating(philo);
	if (first_acquired && second_acquired)
		release_forks(philo, f_mutex, s_mutex);
}
