/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:26:47 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/03 17:39:51 by pablo            ###   ########.fr       */
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

int	start_and_join_behaviours(t_philo *philo)
{
	pthread_t	behaviour_thread_id;
	pthread_t	death_monitor_id;
	pthread_t	death_stop_monitor_id;
	pthread_t	full_monitor_id;
	pthread_t	full_stop_monitor_id;

	// TODO: Si aquí falla, hay que cerrar todos los hilos, por lo que
	// tendré que hacer un semáforo para indicar cierre global
	if (!philo)
		return (1);
	if (pthread_create(&behaviour_thread_id, NULL, philo_behaviour_loop,
			philo) != 0)
	{
		printf(RED "Error: Failed to create behaviour thread\n" RESET);
		return (1);
	}
	if (pthread_create(&death_monitor_id, NULL, death_monitor, philo) != 0)
	{
		printf(RED "Error: Failed to create death monitor thread\n" RESET);
		return (1);
	}
	if (pthread_create(&death_stop_monitor_id, NULL, death_stop_monitor,
			philo) != 0)
	{
		printf(RED "Error: Failed to create death stop monitor thread\n" RESET);
		return (1);
	}
	if (philo->args->n_eat > 0)
	{
		if (pthread_create(&full_monitor_id, NULL, full_monitor, philo) != 0)
		{
			printf(RED "Error: Failed to create death monitor thread\n" RESET);
			return (1);
		}
		if (pthread_create(&full_stop_monitor_id, NULL, full_stop_monitor,
				philo) != 0)
		{
			printf(RED "Error: Failed to create death stop monitor thread\n" RESET);
			return (1);
		}
	}
	pthread_detach(death_stop_monitor_id);
	pthread_detach(death_monitor_id);
	pthread_join(behaviour_thread_id, NULL);
	return (0);
}

static t_philo	*open_semaphore(t_philo *philo)
{
	philo->last_meal_sem = get_sem_numbered("/last_meal_sem", philo->id, 1);
	if (philo->last_meal_sem == NULL)
	{
		// clean_philos(philo);
		exit(1);
		return (NULL);
	}
	philo->local_stop_sem = get_sem_numbered("/local_stop_sem", philo->id, 1);
	if (philo->local_stop_sem == NULL)
	{
		// clean_philos(philo);
		exit(1);
		return (NULL);
	}
	if (philo->args->n_eat > 0)
	{
		philo->local_full_sem = get_sem_numbered("/local_full_sem", philo->id,
				0);
		if (philo->local_full_sem == NULL)
		{
			// clean_philos(philo);
			exit(1);
			return (NULL);
		}
	}
	printf("Creado filósofo con id %i en pid %i\n", philo->id, getpid());
	return (philo);
}

t_philo	*philo_start(t_args *args)
{
	unsigned int	counter;
	t_philo			*tmp_philo;

	counter = 1;
	while (counter <= args->philo_n)
	{
		tmp_philo = create_philo(counter, args);
		if (!tmp_philo)
			// TODO: Si aquí falla, hay que cerrar todos los hilos, por lo que
			// tendré que hacer un semáforo para indicar cierre global
			return (NULL);
		tmp_philo->pid = fork();
		if (tmp_philo->pid == 0)
		{
			start_and_join_behaviours(open_semaphore(tmp_philo));
			return (tmp_philo);
		}
		if (tmp_philo->pid == -1)
		{
			// TODO: Si aquí falla, hay que cerrar todos los hilos, por lo que
			// tendré que hacer un semáforo para indicar cierre global
			free(tmp_philo);
			return (NULL);
		}
		free(tmp_philo);
		++counter;
	}
	return (NULL);
}
