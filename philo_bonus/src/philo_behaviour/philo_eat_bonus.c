/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:11:04 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/03 17:32:59 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

void	philo_eat(t_philo *philo)
{
	safe_sem_wait(philo->args->forks_sem);
	safe_log_printf("%10u" BOLD MAGENTA " %u" RESET GREEN " has taken a fork"
		RESET "\n", philo->id, philo->args, philo);
	safe_sem_wait(philo->args->forks_sem);
	safe_log_printf("%10u" BOLD MAGENTA " %u" RESET GREEN
		" has taken a fork" RESET "\n", philo->id, philo->args, philo);
	safe_log_printf("%10u" BOLD MAGENTA " %u" RESET YELLOW " is eating" RESET
		"\n", philo->id, philo->args, philo);
	set_last_meal(philo, get_time_ms());
	usleep_check(philo->args->time_eat * 1000, philo);
	safe_sem_post(philo->args->forks_sem);
	safe_sem_post(philo->args->forks_sem);
	philo->n_eat++;
}
