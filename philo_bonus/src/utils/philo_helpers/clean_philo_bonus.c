/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:45:01 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/02 14:11:56 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

void	close_sems(t_args *args, int id)
{
	int	status;

	status = 0;
	if (args->forks_sem != SEM_FAILED)
		if (sem_close(args->forks_sem) == -1)
			status = -1;
	if (args->full_sem != SEM_FAILED)
		if (sem_close(args->full_sem) == -1)
			status = -1;
	if (args->stop_sem != SEM_FAILED)
		if (sem_close(args->stop_sem) == -1)
			status = -1;
	if (args->death_sem != SEM_FAILED)
		if (sem_close(args->death_sem) == -1)
			status = -1;
	if (args->printf_sem != SEM_FAILED)
		if (sem_close(args->printf_sem) == -1)
			status = -1;
	if (status == -1)
		printf(RED "Error closing args sempahores in process with philosopher's"
					" ID" MAGENTA "%i " RESET "\n",
				id);
}

void	clean_philos(t_philo *philo)
{
	close_sems(philo->args, philo->id);
	if (philo->last_meal_sem != SEM_FAILED && philo->last_meal_sem != NULL)
	{
		if (sem_close(philo->last_meal_sem) == -1)
		{
			printf(RED "Error closing philosopher's semaphore with id "
				MAGENTA "%i " RESET "\n",
				philo->id);
		}
	}
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
