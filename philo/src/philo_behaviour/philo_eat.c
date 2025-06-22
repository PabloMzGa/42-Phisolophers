/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:53:12 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 00:38:49 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

/**
 * @brief Selects the order of mutexes to avoid deadlock.
 *
 * This function assigns the addresses of two mutexes associated with the
 * philosopher's previous and next forks to the provided pointers, ensuring
 * a consistent locking order based on their memory addresses. This helps
 * prevent deadlocks when multiple philosophers attempt to lock forks.
 *
 * @param[out] first_mutex  Pointer to store the address of the first mutex
 *                          to lock.
 * @param[out] second_mutex Pointer to store the address of the second mutex
 *                          to lock.
 * @param[in]  philo        Pointer to the philosopher structure containing
 *                          fork mutexes.
 */
static void	select_mutex(pthread_mutex_t **first_mutex,
		pthread_mutex_t **second_mutex, t_philo *philo)
{
	if (&(philo->previous->mutex) < &(philo->next->mutex))
	{
		*first_mutex = &(philo->previous->mutex);
		*second_mutex = &(philo->next->mutex);
	}
	else
	{
		*first_mutex = &(philo->next->mutex);
		*second_mutex = &(philo->previous->mutex);
	}
}

static void	philosopher_death(t_philo *philo, pthread_mutex_t *f_mutex,
		pthread_mutex_t *s_mutex)
{
	philo->args->simulation_running = 0;
	if (f_mutex)
		pthread_mutex_unlock(f_mutex);
	if (s_mutex)
		pthread_mutex_unlock(s_mutex);
	printf("%10ld" BOLD MAGENTA " %li" RESET RED " died\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
}

static int	death_checker(t_philo *philo, pthread_mutex_t *f_mutex,
		pthread_mutex_t *s_mutex)
{
	long	current_time;
	long	elapsed;

	current_time = get_time_ms();
	if (current_time < philo->last_meal_timestamp)
		return (philosopher_death(philo, f_mutex, s_mutex), 1);
	elapsed = current_time - philo->last_meal_timestamp;
	if (elapsed > philo->args->time_die)
		return (philosopher_death(philo, f_mutex, s_mutex), 1);
	return (0);
}

void	philosopher_eat(t_philo *philo)
{
	pthread_mutex_t	*f_mutex;
	pthread_mutex_t	*s_mutex;

	select_mutex(&f_mutex, &s_mutex, philo);
	pthread_mutex_lock(f_mutex);
	if (!philo->args->simulation_running || death_checker(philo, f_mutex, NULL))
		return ;
	printf("%10ld" BOLD MAGENTA " %li" RESET GREEN " has taken a fork\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
	pthread_mutex_lock(s_mutex);
	if (!philo->args->simulation_running || death_checker(philo, f_mutex,
			s_mutex))
		return ;
	printf("%10ld" BOLD MAGENTA " %li" RESET GREEN " has taken a fork\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
	printf("%10ld" BOLD MAGENTA " %li" RESET YELLOW " is eating\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
	philo->last_meal_timestamp = get_time_ms();
	usleep(philo->args->time_eat * 1000);
	philo->n_eat++;
	pthread_mutex_unlock(f_mutex);
	pthread_mutex_unlock(s_mutex);
}
