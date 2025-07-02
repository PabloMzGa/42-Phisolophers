/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_printf_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:50:34 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/02 16:52:53 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	safe_single_printf(char *string, t_args *args)
{
	if (safe_sem_wait(args->printf_sem))
		return (1);
	printf("%s", string);
	if (safe_sem_post(args->printf_sem))
		return (1);
	return (0);
}

int	safe_log_printf(char *string, unsigned int id, t_args *args)
{
	unsigned int	stop;

	safe_sem_wait(args->local_stop_sem);
	stop = args->local_stop;
	safe_sem_post(args->local_stop_sem);
	if (!stop)
	{
		if (safe_sem_wait(args->printf_sem))
			return (1);
		printf(string, get_time_ms() - args->epoch, id);
		if (safe_sem_post(args->printf_sem))
			return (1);
	}
	return (0);
}
