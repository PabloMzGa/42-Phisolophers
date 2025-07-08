/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_local_stop_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:42:10 by pablo             #+#    #+#             */
/*   Updated: 2025/07/08 13:47:09 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	set_local_stop(t_philo *philo, unsigned int local_stop)
{
	safe_sem_wait(philo->local_stop_sem);
	philo->local_stop = local_stop;
	safe_sem_post(philo->local_stop_sem);
}
