/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_simulation_running.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:35:01 by pablo             #+#    #+#             */
/*   Updated: 2025/06/23 21:35:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_simulation_running(t_args *args)
{
	int	running;

	if (safe_mutex_lock(&args->simulation_mutex, NULL))
		return (0);
	running = args->simulation_running;
	safe_mutex_unlock(&args->simulation_mutex, NULL);
	return (running);
}
