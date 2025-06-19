/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:03:17 by pablo             #+#    #+#             */
/*   Updated: 2025/06/19 21:07:33 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Gets the current time in milliseconds.
 *
 * This function retrieves the current system time using gettimeofday,
 * and returns the time in milliseconds since the Unix epoch.
 *
 * @return The current time in milliseconds as a long integer.
 */
long	get_time_ms(void)
{
	long			ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}
