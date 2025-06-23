/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:40:55 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 22:06:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

int	safe_mutex_lock(pthread_mutex_t *mutex, t_args *args)
{
	int	status;

	status = pthread_mutex_lock(mutex);
	if (status != 0)
	{
		printf(RED "Error: pthread_mutex_lock failed with code %d\n" RESET,
			status);
		if (args && mutex != &args->simulation_mutex)
		{
			safe_mutex_lock(&args->simulation_mutex, NULL);
			set_simulation_running(args, 0);
			safe_mutex_unlock(&args->simulation_mutex, NULL);
		}
		return (1);
	}
	return (0);
}

int	safe_mutex_unlock(pthread_mutex_t *mutex, t_args *args)
{
	int	status;

	status = pthread_mutex_unlock(mutex);
	if (status != 0)
	{
		printf(RED "Error: pthread_mutex_unlock failed with code %d\n" RESET,
			status);
		if (args && mutex != &args->simulation_mutex)
		{
			set_simulation_running(args, 0);
		}
		return (1);
	}
	return (0);
}
