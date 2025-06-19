/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep_think.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:55:37 by pablo             #+#    #+#             */
/*   Updated: 2025/06/19 23:56:33 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

void	philosopher_sleep_think(t_philo *philo, t_args *args)
{
	printf("%ld" BOLD MAGENTA " %i" RESET BLUE " is sleeping\n" RESET,
		get_time_ms(), philo->id);
	usleep(args->time_sleep * 1000);
	printf("%ld" BOLD MAGENTA " %i" RESET BRIGHT_CYAN " is thinking\n" RESET,
		get_time_ms(), philo->id);
}
