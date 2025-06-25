/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:25:41 by pablo             #+#    #+#             */
/*   Updated: 2025/06/25 19:04:10 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philo(unsigned int id, t_args *args)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->next = NULL;
	philo->previous = NULL;
	philo->id = id;
	philo->n_eat = 0;
	philo->args = args;
	philo->status = HUNGRY;
	philo->last_meal_timestamp = get_time_ms();
	if (pthread_mutex_init(&philo->fork_mutex, NULL) != 0)
		return (free(philo), NULL);
	if (pthread_mutex_init(&philo->internal_mutex, NULL) != 0)
		return (free(philo), NULL);
	return (philo);
}
