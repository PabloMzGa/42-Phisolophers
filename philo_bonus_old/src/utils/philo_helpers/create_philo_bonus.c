/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:48:28 by pablo             #+#    #+#             */
/*   Updated: 2025/07/02 13:21:40 by pabmart2         ###   ########.fr       */
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
	philo->next = NULL;
	philo->last_meal_sem = NULL;
	philo->args = args;
	philo->status = HUNGRY;
	return (philo);
}
