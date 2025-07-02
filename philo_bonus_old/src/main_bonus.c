/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:39:39 by pablo             #+#    #+#             */
/*   Updated: 2025/07/02 16:16:28 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

// TODO: Los cambios en populate_philo han roto el programa y ya no mueren.
//Hay que detectar por qué y ajustar todo lo demás.
//Además, si el monitor full mata a los procesos desde el principal, no hay
//posibilidad de hacer cleanup, así que habría que buscar la forma de
//que al igual que el monitor de muerte, haya un monitor de lleno por cada uno.
//Quizás hacer un "stop_monitor" por cada filósofo, y en vez de matar desde el
//principal, dar paso a ese monitor

int	main(int argc, char *argv[])
{
	t_args	args;
	t_philo	*philo;

	if (!check_args(argc, argv))
		return (1);
	if (set_args(&args, argc, argv))
		return (1);
	printf("Iniciando en pid %i\n", getpid());
	philo = populate_philosophers(&args);
	if (!philo)
		return (1);
	if (philo && philo->pid == 0)
		start_philosophers_behaviour(philo);
	/*
	if (args.n_eat > 0)
	start_full_monitor(philo);
	*/
	while (waitpid(-1, NULL, 0) > 0)
		;
	clean_philos(philo);
	return (0);
}
