/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_monitor_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:08:13 by pablo             #+#    #+#             */
/*   Updated: 2025/07/08 13:10:28 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*full_monitor(void *args)
{
	t_args			*targs;
	unsigned int	i;

	targs = (t_args *)args;
	i = 0;
	while (i < targs->philo_n)
	{
		safe_sem_wait(targs->full_sem);
		++i;
	}
	i = 0;
	while (i < targs->philo_n)
	{
		safe_sem_post(targs->stop_sem);
		++i;
	}
	return (NULL);
}
