/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep_think_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:55:37 by pablo             #+#    #+#             */
/*   Updated: 2025/06/25 18:42:13 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

void	philosopher_sleep_think(t_philo *philo)
{
	printf("%10u" BOLD MAGENTA " %u" RESET BLUE " is sleeping\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
	usleep(philo->args->time_sleep * 1000);
	printf("%10u " BOLD MAGENTA "%u" RESET BRIGHT_CYAN " is thinking\n" RESET,
		get_time_ms() - philo->args->epoch, philo->id);
}
