/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:38:52 by pablo             #+#    #+#             */
/*   Updated: 2025/07/09 16:22:50 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

/**
 * @brief Selects the order of fork mutexes for a philosopher (2 philos).
 *
 * Assigns pointers to the first and second mutexes (forks) that a
 * philosopher should use when attempting to eat. The order depends on
 * the philosopher's ID to help prevent deadlocks.
 *
 * @param first_mutex Pointer to the first mutex pointer to be set.
 * @param second_mutex Pointer to the second mutex pointer to be set.
 * @param philo Pointer to the philosopher structure.
 *
 * @note For philosopher with ID 1, the previous philosopher's fork is
 *       taken first. For philosopher with ID 2, their own fork is
 *       taken first.
 */
static void	select_mutex_2_philo(pthread_mutex_t **first_mutex,
		pthread_mutex_t **second_mutex, t_philo *philo)
{
	if (philo->id == 1)
	{
		*first_mutex = &(philo->previous->fork_mutex);
		*second_mutex = &(philo->fork_mutex);
	}
	else if (philo->id == 2)
	{
		*first_mutex = &(philo->fork_mutex);
		*second_mutex = &(philo->previous->fork_mutex);
	}
}

void	select_mutex(pthread_mutex_t **first_mutex,
		pthread_mutex_t **second_mutex, t_philo *philo)
{
	if (philo->next)
	{
		if (philo->args->philo_n == 2)
		{
			select_mutex_2_philo(first_mutex, second_mutex, philo);
			return ;
		}
		if (&(philo->previous->fork_mutex) < &(philo->next->fork_mutex))
		{
			*first_mutex = &(philo->previous->fork_mutex);
			*second_mutex = &(philo->next->fork_mutex);
		}
		else
		{
			*first_mutex = &(philo->next->fork_mutex);
			*second_mutex = &(philo->previous->fork_mutex);
		}
	}
	else
	{
		*first_mutex = NULL;
		*second_mutex = NULL;
	}
}

int	check_stop(t_philo *philo, pthread_mutex_t *f_mutex,
		pthread_mutex_t *s_mutex)
{
	if (!get_simulation_running(philo->args))
	{
		if (f_mutex)
			safe_mutex_unlock(f_mutex, philo->args);
		if (s_mutex)
			safe_mutex_unlock(s_mutex, philo->args);
		return (1);
	}
	return (0);
}
