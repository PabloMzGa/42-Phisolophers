/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:38:09 by pablo             #+#    #+#             */
/*   Updated: 2025/06/20 00:21:04 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "philosophers.h"

void static	*philosopher_behaviour(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	//TODO: Cambiar el estatus del filósofo si sale del while
	//(es decir, si se ha llenado)
	while (philo->args->n_eat == -1 || philo->args->n_eat != philo->n_eat)
	{
		philosopher_eat(philo, philo->args);
		philosopher_sleep_think(philo, philo->args);
	}
	return (NULL);
}

void	start_philosophers_behaviour(t_philo *philos, t_args *args)
{
	t_philo	*current_philo;
	size_t	i;

	current_philo = philos;
	i = 0;
	while (i < args->philo_n)
	{
		pthread_create(&(current_philo->thread), NULL, philosopher_behaviour,
			(void *)current_philo);
		current_philo = current_philo->next;
		i++;
	}
	current_philo = philos;
	i = 0;
	while (i < args->philo_n)
	{
		pthread_join(current_philo->thread, NULL);
		current_philo = current_philo->next;
		i++;
	}
	//TODO: HAcer una función wait que compruebe el status de los filósofos
	//probablemente con while (1) hasta que un hilo lo actualice.
	//Por limpieza de codigo podría llevarme también el while con los join.

	//TODO: Cleanup de todo, cerrar los hilos con pthread_detatch y
	//pthread_mutex_destroy, asi como los free de t_args y t_philo
}
