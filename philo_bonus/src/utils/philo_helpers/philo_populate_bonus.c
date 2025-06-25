/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_populate_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:33:13 by pablo             #+#    #+#             */
/*   Updated: 2025/06/25 19:05:10 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_philo	*populate_philosophers(t_args *args)
{
	size_t	counter;
	t_philo	*tmp_philo;

	counter = 0;
	while (counter < args->philo_n)
	{
		++counter;
		tmp_philo = create_philo(counter, args);
		if (!tmp_philo)
			//TODO: Esto debería ir a algún cleanup que se encargue de matar
			//todos los procesos que se hayan creado previamente.
			return (NULL);
		tmp_philo->pid = fork();
		if (tmp_philo->pid != 0)
			free(tmp_philo);
		else
			return (tmp_philo);
	}
	return (NULL);
}
