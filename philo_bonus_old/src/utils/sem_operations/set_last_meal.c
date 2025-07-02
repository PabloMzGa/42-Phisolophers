/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_last_meal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:42:10 by pablo             #+#    #+#             */
/*   Updated: 2025/06/26 20:49:16 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	set_last_meal(t_philo *philo, unsigned int last_meal)
{
	safe_sem_wait(philo->last_meal_sem);
	philo->last_meal_timestamp = last_meal;
	safe_sem_post(philo->last_meal_sem);
	return (last_meal);
}
