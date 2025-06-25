/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:11:04 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/25 18:42:13 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

void	philosopher_eat(t_philo *philo)
{
	sem_wait(philo->args->forks_sem);
	printf("%10u" BOLD MAGENTA " %u" RESET GREEN " has taken a fork\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
	sem_wait(philo->args->forks_sem);
	printf("%10u" BOLD MAGENTA " %u" RESET GREEN " has taken a fork\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
	printf("%10u" BOLD MAGENTA " %u" RESET YELLOW " is eating\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
	philo->last_meal_timestamp = get_time_ms();
	usleep(philo->args->time_eat * 1000);
	sem_post(philo->args->forks_sem);
	sem_post(philo->args->forks_sem);
	philo->n_eat++;
}
