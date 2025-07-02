/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep_think_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:55:37 by pablo             #+#    #+#             */
/*   Updated: 2025/06/30 14:08:41 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

void	philosopher_sleep_think(t_philo *philo)
{
	struct timeval	time;
	int delay;


	safe_log_printf("%10u" BOLD MAGENTA " %u" RESET BLUE " is sleeping" RESET
		"\n", philo->id, philo->args);
		usleep(philo->args->time_sleep * 1000);
	gettimeofday(&time, NULL);
	delay = ((time.tv_usec + philo->id * 17 + philo->n_eat * 13) % 10) * 1000;
	if (delay)
		usleep(delay);
	safe_log_printf("%10u " BOLD MAGENTA "%u" RESET BRIGHT_CYAN " is thinking"
		RESET "\n", philo->id, philo->args);
}
