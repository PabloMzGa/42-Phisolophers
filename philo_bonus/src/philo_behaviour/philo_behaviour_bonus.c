/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:26:47 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/04 17:01:35 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

void	*philo_behaviour_loop(void *args)
{
	t_philo			*philo;
	unsigned int	local_stop;
	int		lone_fork;

	philo = (t_philo *)args;
	lone_fork = 0;
	get_local_stop(philo, &local_stop);
	while (!local_stop)
	{
		if (lone_fork == 0)
			philo_eat(philo);
		if (philo->args->philo_n == 1)
			lone_fork = 1;
		if (philo->args->n_eat > 0 && philo->n_eat >= philo->args->n_eat)
			sem_post(philo->args->full_sem);
		get_local_stop(philo, &local_stop);
		if (!local_stop && philo->args->philo_n > 1)
			philo_sleep_think(philo);
	}
	return (NULL);
}
