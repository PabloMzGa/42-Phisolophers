/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:26:47 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/26 13:57:54 by pablo            ###   ########.fr       */
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


void	start_philosophers_behaviour(t_philo *philo)
{
	//pthread_t	monitor_thread;

	philosopher_behaviour(philo);
}
