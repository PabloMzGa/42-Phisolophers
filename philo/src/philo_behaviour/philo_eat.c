/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:53:12 by pablo             #+#    #+#             */
/*   Updated: 2025/06/20 00:20:11 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

/**
 * @brief Selects the order of mutexes to avoid deadlock.
 *
 * This function assigns the addresses of two mutexes associated with the
 * philosopher's previous and next forks to the provided pointers, ensuring
 * a consistent locking order based on their memory addresses. This helps
 * prevent deadlocks when multiple philosophers attempt to lock forks.
 *
 * @param[out] first_mutex  Pointer to store the address of the first mutex
 *                          to lock.
 * @param[out] second_mutex Pointer to store the address of the second mutex
 *                          to lock.
 * @param[in]  philo        Pointer to the philosopher structure containing
 *                          fork mutexes.
 */
static void	select_mutex(
		pthread_mutex_t **first_mutex,
		pthread_mutex_t **second_mutex,
		t_philo *philo)
{
	if (&(philo->previous->mutex) < &(philo->next->mutex))
	{
		*first_mutex = &(philo->previous->mutex);
		*second_mutex = &(philo->next->mutex);
	}
	else
	{
		*first_mutex = &(philo->next->mutex);
		*second_mutex = &(philo->previous->mutex);
	}
}

void	philosopher_eat(t_philo *philo, t_args *args)
{
	//TODO: Añadir la comprobación de la espera y la muerte de hambre, con el
	//cambio de estatus concreto.
	//Además, habría que lanzar el mensaje de muerte inmediatamente, antes
	//de nada.
	pthread_mutex_t	*first_mutex;
	pthread_mutex_t	*second_mutex;

	select_mutex(&first_mutex, &second_mutex, philo);
	pthread_mutex_lock(first_mutex);
	printf("%ld" BOLD MAGENTA " %i" RESET GREEN " has taken a fork\n" RESET,
		get_time_ms(), philo->id);
	pthread_mutex_lock(second_mutex);
	printf("%ld" BOLD MAGENTA " %i" RESET GREEN " has taken a fork\n" RESET,
		get_time_ms(), philo->id);
	printf("%ld" BOLD MAGENTA " %i" RESET YELLOW " is eating\n" RESET,
		get_time_ms(), philo->id);
	usleep(args->time_eat * 1000);
	philo->n_eat++;
	pthread_mutex_unlock(first_mutex);
	pthread_mutex_unlock(second_mutex);
}
