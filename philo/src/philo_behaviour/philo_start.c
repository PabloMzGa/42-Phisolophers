/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:38:09 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 00:23:14 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

static void	*philosopher_behaviour(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while ((philo->args->n_eat == -1 || philo->args->n_eat != philo->n_eat)
		&& philo->args->simulation_running)
	{
		philosopher_eat(philo);
		if (philo->status == HUNGRY && philo->args->simulation_running)
			philosopher_sleep_think(philo);
	}
	if (philo->args->n_eat != -1 && philo->n_eat >= philo->args->n_eat)
		philo->status = FULL;
	return (NULL);
}

void	start_philosophers_behaviour(t_philo *philos)
{
	t_philo	*current_philo;
	size_t	i;

	current_philo = philos;
	i = 0;
	while (i < philos->args->philo_n)
	{
		pthread_create(&(current_philo->thread), NULL, philosopher_behaviour,
			(void *)current_philo);
		current_philo = current_philo->next;
		i++;
	}
	wait_philo_end(philos);
}
