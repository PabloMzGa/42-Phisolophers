/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_philo_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:33:13 by pablo             #+#    #+#             */
/*   Updated: 2025/06/26 19:50:08 by pablo            ###   ########.fr       */
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
static t_philo	*open_semaphores(t_philo *philo)
{
	philo->last_meal_sem = get_sem_numbered("/last_meal_sem", philo->id, 1);
	if (philo->last_meal_sem == NULL)
		return (NULL);
	return (philo);
}

t_philo	*populate_philosophers(t_args *args)
{
	unsigned int	counter;
	t_philo			*tmp_philo1;
	t_philo			*tmp_philo2;

	counter = 1;
	tmp_philo1 = create_philo(counter, args);
	tmp_philo1->pid = fork();
	if (tmp_philo1->pid == 0)
		return (open_semaphores(tmp_philo1));
	tmp_philo2 = NULL;
	if (!tmp_philo1)
		return (NULL);
	while (counter < args->philo_n)
	{
		++counter;
		tmp_philo2 = create_philo(counter, args);
		if (!tmp_philo2)
			// TODO: Esto debería ir a algún cleanup que se encargue de matar
			// todos los procesos que se hayan creado previamente
			return (NULL);
		add_philo(&tmp_philo1, tmp_philo2);
		tmp_philo2->pid = fork();
		if (tmp_philo2->pid == 0)
			return (open_semaphores(tmp_philo2));
	}
	return (tmp_philo1);
}
/*
t_philo	*populate_philosophers(t_args *args)
{
	unsigned int	counter;
	t_philo			*tmp_philo;

	counter = 0;
	while (counter < args->philo_n)
	{
		++counter;
		tmp_philo = create_philo(counter, args);
		if (!tmp_philo)
		// TODO: Esto debería ir a algún cleanup que se encargue de matar
			// todos los procesos que se hayan creado previamente.
			return (NULL);
			tmp_philo->pid = fork();
			if (tmp_philo->pid != 0)
			free(tmp_philo);
			else
			return (open_semaphores(tmp_philo));
		}
		return (NULL);
	}
	*/
