/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:11:04 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/26 14:01:34 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

void	philosopher_eat(t_philo *philo)
{
	safe_sem_wait(philo->args->forks_sem);
	printf("%10u" BOLD MAGENTA " %u" RESET GREEN " has taken a fork\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
	safe_sem_wait(philo->args->forks_sem);
	printf("%10u" BOLD MAGENTA " %u" RESET GREEN " has taken a fork\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
	printf("%10u" BOLD MAGENTA " %u" RESET YELLOW " is eating\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
	philo->last_meal_timestamp = get_time_ms();
	usleep(philo->args->time_eat * 1000);
	safe_sem_post(philo->args->forks_sem);
	safe_sem_post(philo->args->forks_sem);
	philo->n_eat++;
}
