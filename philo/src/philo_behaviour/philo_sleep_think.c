/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep_think.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:55:37 by pablo             #+#    #+#             */
/*   Updated: 2025/07/08 14:02:13 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

void	philosopher_sleep_think(t_philo *philo)
{
	if (get_simulation_running(philo->args))
	{
		if (safe_log_printf("%10u" BOLD MAGENTA
				" %u" RESET BLUE " is sleeping\n" RESET,
				philo->id, philo->args))
			return ;
	}
	usleep_check(philo->args->time_sleep, philo->args);
	if (get_simulation_running(philo->args))
		safe_log_printf("%10u " BOLD MAGENTA "%u" RESET BRIGHT_CYAN
			" is thinking\n" RESET, philo->id, philo->args);
}
