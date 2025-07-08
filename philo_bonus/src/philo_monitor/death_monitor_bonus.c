/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:08:13 by pablo             #+#    #+#             */
/*   Updated: 2025/07/08 13:58:44 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*death_monitor(void *args)
{
	t_philo			*philo;
	int				is_dead;
	unsigned int	counter;
	unsigned int	local_stop;

	philo = (t_philo *)args;
	is_dead = 0;
	counter = 0;
	while (!is_dead)
	{
		get_local_stop(philo, &local_stop);
		if (local_stop)
			return (safe_sem_post(philo->death_monitor_end_sem), NULL);
		is_dead = check_philo_death(philo);
	}
	while (counter < philo->args->philo_n)
	{
		safe_sem_post(philo->args->stop_sem);
		++counter;
	}
	return (safe_sem_post(philo->death_monitor_end_sem), NULL);
}
