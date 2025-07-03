/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_check_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:23:38 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/03 15:01:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	usleep_check(unsigned int sleep, t_philo *philo)
{
	unsigned int	sleep_counter;
	unsigned int	next_microsleep;
	unsigned int	start_time;
	unsigned int	local_stop;

	start_time = get_time_ms();
	sleep_counter = 0;
	sleep = sleep / 1000;
	get_local_stop(philo, &local_stop);
	while (sleep_counter < sleep && !local_stop)
	{
		if (sleep - sleep_counter < 10)
			next_microsleep = sleep - sleep_counter;
		else
			next_microsleep = 10;
		usleep(next_microsleep * 1000);
		sleep_counter = get_time_ms() - start_time;
		get_local_stop(philo, &local_stop);
	}
}
