/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:23:38 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/08 14:06:24 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	usleep_check(unsigned int sleep, t_args *args)
{
	unsigned int	sleep_counter;
	unsigned int	next_microsleep;

	sleep_counter = 0;
	while (sleep_counter < sleep)
	{
		if (!get_simulation_running(args))
			return ;
		if (sleep - sleep_counter < MICROSLEEP_MS)
			next_microsleep = sleep - sleep_counter;
		else
			next_microsleep = MICROSLEEP_MS;
		usleep(next_microsleep * 1000);
		sleep_counter += next_microsleep;
	}
}
