/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_monitor_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:08:13 by pablo             #+#    #+#             */
/*   Updated: 2025/07/03 17:59:03 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/**TODO: No puedo hacer esto, ya que en bucle while de full_stop_monitor nada
 * asegura que se consuma 1 por cada proceso. Habría que hacer:
 *
 * - Cuando full monitor deje de esperar a local_full_sem, debería hacer post
 * a un semáforo global (args->full_sem). Quizás esto lo puedo ahorrar, haciendo
 * el post directamente tras el philo_eat (y así ahorrar un semáforo).
 *
 * - Cuando en el monitor central se hagan los suficientes waits (n_philo),
 * el monitor central hace un post a un nuevo semáforo local cuyo nombre sera
 * "X_semN", siendo N la id. Hay que tener en cuenta que estos semáforos
 * NO PUEDEN SER UNLINKEADOS en la creación, para poder hacer open
 * en el monitor central.
 *
 * - Cada proceso tendrá un hilo esperando a "X_semN", que en el momento que se
 * abra, terminará con el proceso poniendo a 1 set_local_stop()
*/


void	*full_monitor(void *args)
{
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	philo = (t_philo *)args;
	sem_wait(philo->local_full_sem);
	while (i < philo->args->philo_n)
	{
		sem_post(philo->args->full_sem);
		++i;
	}
	printf("DEBUG: Filósofo %i lleno\n", philo->id);
	return (NULL);
}

void	*full_stop_monitor(void *args)
{
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	philo = (t_philo *)args;
	while (i < philo->args->philo_n)
	{
		sem_wait(philo->args->full_sem);
		printf ("DEBUG: Esperado una vez en id %i\n", philo->id);
	}
	safe_single_printf(BOLD GREEN "All philosophers have eaten the target "
			"number of times, ending simulation\n" RESET, philo->args);
	set_local_stop(philo, 1);
	return (NULL);
}
