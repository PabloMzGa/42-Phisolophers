/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep_think.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:55:37 by pablo             #+#    #+#             */
/*   Updated: 2025/06/24 12:15:56 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

void	philosopher_sleep_think(t_philo *philo)
{
	int	still_running;

	if (safe_log_printf("%10ld" BOLD MAGENTA " %li" RESET BLUE " is sleeping\n"
		RESET, get_time_ms() - philo->args->epoch, philo->id, philo->args))
		return ;
	usleep(philo->args->time_sleep * 1000);
	still_running = get_simulation_running(philo->args);
	if (still_running)
		safe_log_printf("%10ld " BOLD MAGENTA "%li" RESET BRIGHT_CYAN
			" is thinking\n" RESET, get_time_ms() - philo->args->epoch,
			philo->id, philo->args);
}
