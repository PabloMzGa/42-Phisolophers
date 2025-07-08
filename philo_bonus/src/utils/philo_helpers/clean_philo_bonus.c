/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:45:01 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/08 14:01:46 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	close_args_sems(t_args *args)
{
	if (args->forks_sem && args->forks_sem != SEM_FAILED)
		sem_close(args->forks_sem);
	if (args->stop_sem && args->stop_sem != SEM_FAILED)
		sem_close(args->stop_sem);
	if (args->printf_sem && args->printf_sem != SEM_FAILED)
		sem_close(args->printf_sem);
	if (args->n_eat > 0)
	{
		if (args->full_sem && args->full_sem != SEM_FAILED)
			sem_close(args->full_sem);
	}
}

void	clean_philos(t_philo *philo)
{
	close_args_sems(philo->args);
	if (philo->last_meal_sem != SEM_FAILED && philo->last_meal_sem != NULL)
		sem_close(philo->last_meal_sem);
	if (philo->local_stop_sem != SEM_FAILED && philo->local_stop_sem != NULL)
		sem_close(philo->local_stop_sem);
	if (philo->death_monitor_end_sem != SEM_FAILED
		&& philo->death_monitor_end_sem != NULL)
		sem_close(philo->death_monitor_end_sem);
	free(philo);
}
