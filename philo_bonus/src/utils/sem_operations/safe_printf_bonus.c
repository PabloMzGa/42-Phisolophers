/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_printf_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:50:34 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/03 16:36:31 by pablo            ###   ########.fr       */
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

int	safe_log_printf(char *string, unsigned int id, t_args *args,
		t_philo *philo)
{
	unsigned int stop;
	if (philo)
	{
		get_local_stop(philo, &stop);
		if (stop)

			return (0);
	}
	if (safe_sem_wait(args->printf_sem))
		return (1);
	printf(string, get_time_ms() - args->epoch, id);
	if (safe_sem_post(args->printf_sem))
		return (1);
	return (0);
}
