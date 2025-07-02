/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_local_stop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:00:00 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/02 17:06:53 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/**
 * @brief Safely sets the local_stop variable using semaphore protection.
 *
 * This function uses the local_stop_sem semaphore to safely update
 * the local_stop variable in a multi-threaded environment.
 *
 * @param args Pointer to the arguments structure containing the semaphore
 *             and the local_stop variable.
 * @param value The new value to set for local_stop (0 for continue, 1 for stop).
 * @return int Returns 0 on success, 1 on failure.
 */
int	set_local_stop(t_args *args, unsigned int value)
{
	if (safe_sem_wait(args->local_stop_sem))
		return (1);
	args->local_stop = value;
	if (safe_sem_post(args->local_stop_sem))
		return (1);
	return (0);
}
