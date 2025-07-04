/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_monitor_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:52:58 by pablo             #+#    #+#             */
/*   Updated: 2025/07/04 13:40:26 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*stop_monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (!philo->args->stop_sem)
		return (NULL);
	sem_wait(philo->args->stop_sem);
	set_local_stop(philo, 1);
	return (NULL);
}
