/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:15:00 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 22:35:46 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_philo_status(t_philo *philo, int status)
{
	if (safe_mutex_lock(&philo->internal_mutex, philo->args) == 0)
	{
		philo->status = status;
		safe_mutex_unlock(&philo->internal_mutex, philo->args);
	}
}
