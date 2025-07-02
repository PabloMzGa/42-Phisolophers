/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_main_thread_ended_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:42:10 by pablo             #+#    #+#             */
/*   Updated: 2025/07/02 18:12:08 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	set_main_thread_ended(t_philo *philo, unsigned int main_thread_ended)
{
	safe_sem_wait(philo->main_thread_ended_sem);
	philo->last_meal_timestamp = main_thread_ended;
	safe_sem_post(philo->main_thread_ended_sem);
	return (main_thread_ended);
}
