/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_philo_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:33:13 by pablo             #+#    #+#             */
/*   Updated: 2025/07/02 16:53:59 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/**
 * @brief Opens and assigns numbered semaphores for a philosopher instance.
 *
 * This function initializes the semaphores required for a philosopher,
 * specifically the printf and last_meal semaphores, using the philosopher's
 * identifier. If any semaphore fails to open, the function returns NULL.
 *
 * @param philo Pointer to the philosopher structure to populate with
 *              semaphores.
 * @return Pointer to the philosopher structure on success, or NULL on
 *         failure.
 */
static t_philo	*open_semaphore(t_philo *philo)
{
	philo->last_meal_sem = get_sem_numbered("/last_meal_sem", philo->id, 1);
	if (philo->last_meal_sem == NULL)
	{
		clean_philos(philo);
		exit(1);
		return (NULL);
	}
	philo->args->local_stop_sem = get_sem_numbered("/local_stop_sem", philo->id, 1);
	if (philo->args->local_stop_sem == NULL)
	{
		clean_philos(philo);
		exit(1);
		return (NULL);
	}
	printf("Creado filósofo con id %i en pid %i\n", philo->id, getpid());
	return (philo);
}

t_philo	*populate_philosophers(t_args *args)
{
	unsigned int	counter;
	t_philo			*tmp_philo;

	counter = 1;
	while (counter <= args->philo_n)
	{
		tmp_philo = create_philo(counter, args);
		if (!tmp_philo)
			return (NULL);
		tmp_philo->pid = fork();
		if (tmp_philo->pid == 0)
			return (open_semaphore(tmp_philo));
		else if (tmp_philo->pid == -1)
			return (free(tmp_philo), NULL);
		free(tmp_philo);
		++counter;
	}
	return (NULL);
}

/*
t_philo	*populate_philosophers(t_args *args)
{
	unsigned int	counter;
	t_philo			*tmp_philo1;
	t_philo			*tmp_philo2;

	counter = 1;
	tmp_philo1 = create_philo(counter, args);
	if (!tmp_philo1)
	return (NULL);
	tmp_philo1->pid = fork();
	if (tmp_philo1->pid == 0)
	return (open_semaphores(tmp_philo1));
	else if (tmp_philo1->pid == -1)
	return (clean_philos(tmp_philo1), NULL);
	tmp_philo2 = NULL;
	if (!tmp_philo1)
	return (NULL);
	while (counter < args->philo_n)
	{
		++counter;
		tmp_philo2 = create_philo(counter, args);
		if (!tmp_philo2)
		return (clean_philos(tmp_philo1), NULL);
		add_philo(&tmp_philo1, tmp_philo2);
		tmp_philo2->pid = fork();
		if (tmp_philo2->pid == 0)
		return (open_semaphores(tmp_philo2));
		else if (tmp_philo2->pid == -1)
		return (clean_philos(tmp_philo1), NULL);
	}
	return (tmp_philo1);
}
*/
