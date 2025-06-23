/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_philo_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:45:42 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 21:56:24 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_philo_status(t_philo *philo)
{
	int	status;

	if (safe_mutex_lock(&philo->internal_mutex, philo->args))
		return (-1);
	status = philo->status;
	safe_mutex_unlock(&philo->internal_mutex, philo->args);
	return (status);
}
