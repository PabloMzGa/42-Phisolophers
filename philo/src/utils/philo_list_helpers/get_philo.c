/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:40:14 by pablo             #+#    #+#             */
/*   Updated: 2025/06/19 22:55:22 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*get_philo(t_philo *philos, size_t id)
{
	t_philo	*start;

	if (!philos)
		return (NULL);
	start = philos;
	while (philos)
	{
		if (philos->id == id)
			return (philos);
		philos = philos->next;
		if (philos == start)
			return (NULL);
	}
	return (NULL);
}
