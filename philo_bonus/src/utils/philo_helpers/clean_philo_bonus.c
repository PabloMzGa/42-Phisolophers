/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:45:01 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/04 16:57:23 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
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
	printf("Limpiando filósofo con id %i en pid %i\n", philo->id, getpid());
	close_args_sems(philo->args);
	if (philo->last_meal_sem != SEM_FAILED && philo->last_meal_sem != NULL)
		sem_close(philo->last_meal_sem);
	if (philo->local_stop_sem != SEM_FAILED && philo->local_stop_sem != NULL)
		sem_close(philo->local_stop_sem);
	free(philo);
}

/*
#include <unistd.h>

void	clean_philos(t_philo *philo)
{
	t_philo	*tmp_philo;
	t_philo	*next;
	t_args	*args;

	int id;
	args = philo->args;
	tmp_philo = philo;
	id = philo->id;
	printf(YELLOW "Limpiando filosofos en id %i y PID %i" RESET "\n",
		philo->id, getpid());
	while (tmp_philo)
	{
		next = tmp_philo->next;
		if (tmp_philo->pid > 0)
		{
			printf ("Suicidando philo id %i con PID %i \n", tmp_philo->id,
				getpid());
			kill(tmp_philo->pid, SIGTERM);
		}
		if (tmp_philo->last_meal_sem != SEM_FAILED
			&& tmp_philo->last_meal_sem != NULL) {
			if (sem_close(tmp_philo->last_meal_sem) == -1) {
				printf(RED "Error closing philosopher's semaphore with id "
					MAGENTA "%i " RESET "\n", tmp_philo->id);
				}
			}
			printf("Liberando philo con id %i en PID %i \n", tmp_philo->id,
				getpid());
			free(tmp_philo);
			tmp_philo = next;
		}
		if (args)
		close_sems(args, id);
	}
*/
