/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:48:28 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 19:33:38 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:25:41 by pablo             #+#    #+#             */
/*   Updated: 2025/06/04 13:40:06 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philo(size_t id, t_args *args)
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
