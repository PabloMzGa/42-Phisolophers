/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep_think_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:55:37 by pablo             #+#    #+#             */
/*   Updated: 2025/06/26 15:37:27 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

void	philosopher_sleep_think(t_philo *philo)
{
	safe_log_printf("%10u" BOLD MAGENTA " %u" RESET BLUE " is sleeping" RESET
		"\n", philo->id, philo->args);
	usleep(philo->args->time_sleep * 1000);
	safe_log_printf("%10u " BOLD MAGENTA "%u" RESET BRIGHT_CYAN " is thinking"
		RESET "\n", philo->id, philo->args);
}
