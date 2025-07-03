/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_local_stop_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:42:10 by pablo             #+#    #+#             */
/*   Updated: 2025/07/03 11:33:55 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	set_local_stop(t_philo *philo, unsigned int local_stop)
{
	safe_sem_wait(philo->local_stop_sem);
	philo->local_stop = local_stop;
	safe_sem_post(philo->local_stop_sem);
	return (local_stop);
}
