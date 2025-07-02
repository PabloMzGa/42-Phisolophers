/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_stop_sem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:47:22 by pablo             #+#    #+#             */
/*   Updated: 2025/07/02 16:53:16 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**
 * @brief Waits on the stop semaphore for each philosopher.
 *
 * This function iterates through the number of philosophers and performs a wait
 * operation on the stop semaphore for each one. It is typically used to ensure
 * that all philosopher processes have reached a certain stopping point before
 * proceeding.
 *
 * @param args Pointer to the arguments structure containing the number of
 * philosophers and the stop semaphore.

 void	set_stop_sem(t_args *args)
 {
	unsigned int	i;

	i = 0;
	while (i < args->philo_n)
	{
		sem_wait(args->stop_sem);
		++i;
	}
}
*/
