/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:26:47 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/11 13:17:04 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/**
 * @brief Handles the special case when there is only one philosopher
 *        (lone fork scenario).
 *
 * This function checks if the number of philosophers is one. If so, it sets
 * the lone_fork flag to indicate that the philosopher is alone and can only
 * pick up one fork.
 *
 * @param philo Pointer to the philosopher structure containing arguments.
 * @param lone_fork Pointer to an integer flag that will be set to 1 if there
 *        is only one philosopher.
 */
static void	handle_lone_fork(t_philo *philo, int *lone_fork)
{
	if (philo->args->philo_n == 1)
		*lone_fork = 1;
}

/**
 * @brief Handles the semaphore signaling when a philosopher has eaten enough
 *        times.
 *
 * This function checks if the philosopher has reached or exceeded the required
 * number of meals (`n_eat`). If so, it posts to the `full_sem` semaphore to
 * signal that this philosopher is "full" (i.e., has finished eating the
 * required number of times).
 *
 * @param philo Pointer to the philosopher structure containing eating state
 *        and arguments.
 */
static void	handle_full_sem(t_philo *philo)
{
	if (philo->args->n_eat > 0 && philo->n_eat >= philo->args->n_eat)
		sem_post(philo->args->full_sem);
}

void	*philo_behaviour_loop(void *args)
{
	t_philo			*philo;
	unsigned int	local_stop;
	int				lone_fork;

	philo = (t_philo *)args;
	lone_fork = 0;
	set_last_meal(philo, get_time_ms());
	get_local_stop(philo, &local_stop);
	while (!local_stop)
	{
		if (lone_fork == 0 && philo_eat(philo))
			break ;
		handle_lone_fork(philo, &lone_fork);
		handle_full_sem(philo);
		get_local_stop(philo, &local_stop);
		if (!local_stop && philo->args->philo_n > 1 && philo_sleep_think(philo))
			break ;
	}
	return (NULL);
}
