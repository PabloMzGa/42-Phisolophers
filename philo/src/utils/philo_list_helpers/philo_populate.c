/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_populate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:33:13 by pablo             #+#    #+#             */
/*   Updated: 2025/06/25 18:35:19 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*populate_philosophers(t_args *args)
{
	unsigned int	counter;
	t_philo			*tmp_philo1;
	t_philo			*tmp_philo2;

	counter = 1;
	tmp_philo1 = create_philo(counter, args);
	tmp_philo2 = NULL;
	if (!tmp_philo1)
		return (NULL);
	while (counter < args->philo_n)
	{
		++counter;
		tmp_philo2 = create_philo(counter, args);
		if (!tmp_philo2)
			return (clean_philos(&tmp_philo1), NULL);
		add_philo(&tmp_philo1, tmp_philo2);
	}
	if (tmp_philo2)
	{
		tmp_philo1->previous = tmp_philo2;
		tmp_philo2->next = tmp_philo1;
	}
	return (tmp_philo1);
}
