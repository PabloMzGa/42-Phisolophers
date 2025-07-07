/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:48:28 by pablo             #+#    #+#             */
/*   Updated: 2025/07/07 17:50:29 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_philo	*create_philo(unsigned int id, t_args *args)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->n_eat = 0;
	philo->last_meal_timestamp = get_time_ms();
	philo->last_meal_sem = NULL;
	philo->local_stop = 0;
	philo->local_stop_sem = NULL;
	philo->args = args;
	return (philo);
}
