/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:11:04 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/02 17:05:02 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

void	philosopher_eat(t_philo *philo)
{
	safe_sem_wait(philo->args->forks_sem);
	safe_log_printf("%10u" BOLD MAGENTA " %u" RESET GREEN " has taken a fork"
		RESET "\n", philo->id, philo->args);
	safe_sem_wait(philo->args->forks_sem);
	safe_log_printf("%10u" BOLD MAGENTA " %u" RESET GREEN
		" has taken a fork" RESET "\n", philo->id, philo->args);
	safe_log_printf("%10u" BOLD MAGENTA " %u" RESET YELLOW " is eating" RESET
		"\n", philo->id, philo->args);
	set_last_meal(philo, get_time_ms());
	usleep(philo->args->time_eat * 1000);
	safe_sem_post(philo->args->forks_sem);
	safe_sem_post(philo->args->forks_sem);
	philo->n_eat++;
}
