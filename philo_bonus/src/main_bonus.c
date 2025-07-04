/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:39:39 by pablo             #+#    #+#             */
/*   Updated: 2025/07/04 17:04:47 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

/** TODO: Creo que hay una condición de carrera cuando uso full_monitor y
 * death_monitor. Puede ocurrir que ambos intenten acabar con el proceso y
 * se bloquea. Si mueren mientras el full monitor está activo, el proceso
 * se queda bloqueado esperando a full_sem. Necesito encontrar la forma de
 * salir de ese proceso (quizas con kill?)
 */

int	main(int argc, char *argv[])
{
	t_args		args;
	t_philo		*philo;
	pthread_t	full_monitor_id;

	if (!check_args(argc, argv))
		return (1);
	if (set_args(&args, argc, argv))
		return (1);
	   if (args.n_eat > 0)
	   {
			   if (pthread_create(&full_monitor_id, NULL, full_monitor, &args) != 0)
			   {
					   printf(RED "Error: Failed to create death stop monitor thread\n" RESET);
					   return (1);
			   }
	   }
	printf("Iniciando en pid %i\n", getpid());
	philo = philo_start(&args);
	if (!philo)
	{
		while (waitpid(-1, NULL, 0) > 0)
			;
		close_args_sems(&args);
		pthread_join(full_monitor_id, NULL);
	}
	else
		clean_philos(philo);
	return (0);
}
