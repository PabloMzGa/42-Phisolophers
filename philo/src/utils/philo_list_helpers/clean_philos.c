/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:15:24 by pablo             #+#    #+#             */
/*   Updated: 2025/06/22 23:51:44 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_philos(t_philo **philo)
{
	t_philo	*tmp_philo;
	t_philo	*next_philo;

	if (!philo || !*philo)
		return ;
	if ((*philo)->previous)
		(*philo)->previous->next = NULL;
	tmp_philo = *philo;
	while (tmp_philo)
	{
		next_philo = tmp_philo->next;
		pthread_mutex_destroy(&tmp_philo->mutex);
		free(tmp_philo);
		tmp_philo = next_philo;
	}
	*philo = NULL;
}
