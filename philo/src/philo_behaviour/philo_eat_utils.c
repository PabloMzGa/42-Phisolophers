/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:38:52 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 21:48:19 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

void	select_mutex(pthread_mutex_t **first_mutex,
		pthread_mutex_t **second_mutex, t_philo *philo)
{
	if (philo->next)
	{
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
