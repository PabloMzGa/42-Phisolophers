/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:15:24 by pablo             #+#    #+#             */
/*   Updated: 2025/07/09 14:39:22 by pabmart2         ###   ########.fr       */
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
		pthread_mutex_destroy(&tmp_philo->fork_mutex);
		pthread_mutex_destroy(&tmp_philo->internal_mutex);
		free(tmp_philo);
		tmp_philo = next_philo;
	}
	*philo = NULL;
}
