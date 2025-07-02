/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:26:47 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/02 18:11:41 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/** TODO: Crear dos monitores, uno para cuando se detecte una muerte,
 * otro para cuando se hayan llenado todos. Este segundo sólo se creará
 * en caso de que philo->args->n_eat != -1.
 *
 * El semáforo de muerte, cuando un proceso hijo muera, hará tantos
 * sem_post como Nº de filósofos. De esta forma "llenamos" el semáforo
 * de muerte para que cada proceso que esté haciendo wait pueda llegar al
 * exit.
 *
 * El semáforo de llenado, se irá haciendo un post cada vez que un
 * filósofo se llene. Existirá entonces un hilo en el proceso principal
 * que hará de monitor de "llenado". Este hará tantos waits como Nº de
 * filósofos, y al terminar, hará tantos post del stop_sem como sean
 * necesarios para activar los monitores locales de cada hijo.
 */

void	*philo_behaviour_loop(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	while (1)
	{
		philo_eat(philo);
		/*
		if (philo->status != FULL && philo->args->n_eat != 0
		&& philo->n_eat >= philo->args->n_eat)
		{
			philo->status = FULL;
			safe_sem_post(philo->args->full_sem);
		}
		*/
		philo_sleep_think(philo);
	}
}
