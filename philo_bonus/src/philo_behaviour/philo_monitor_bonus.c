/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:08:13 by pablo             #+#    #+#             */
/*   Updated: 2025/06/24 17:07:09 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

static void	*monitor_routine(void *args)
{
	t_philo	*philo;
	int		all_full;
	int		someone_died;

	philo = (t_philo *)args;
	sem_wait(philo->args->stop_sem);
	clean_philo(philo);
	exit (0);
	return (NULL);
}

pthread_t	start_monitor(t_philo *philos)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor_routine, philos) != 0)
	{
		printf(RED "Error: Failed to create monitor thread\n" RESET);
		return (0);
	}
	return (monitor_thread);
}
