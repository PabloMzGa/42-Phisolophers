/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep_think.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:55:37 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 00:38:49 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

void	philosopher_sleep_think(t_philo *philo)
{
	printf("%10ld" BOLD MAGENTA " %li" RESET BLUE " is sleeping\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
	usleep(philo->args->time_sleep * 1000);
	if (philo->args->simulation_running)
		printf("%10ld " BOLD MAGENTA
			"%li" RESET BRIGHT_CYAN " is thinking\n" RESET,
			 get_time_ms() - philo->args->epoch, philo->id);
}
