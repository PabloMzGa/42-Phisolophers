/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:39:39 by pablo             #+#    #+#             */
/*   Updated: 2025/06/26 20:07:42 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

// TODO: Proteger los printf con un mutex

int	main(int argc, char *argv[])
{
	t_args	args;
	t_philo	*philo;

	if (!check_args(argc, argv))
		return (1);
	if (set_args(&args, argc, argv))
		return (1);
	philo = populate_philosophers(&args);
	if (philo && philo->pid == 0)
		start_philosophers_behaviour(philo);
	if (args.n_eat > 0)
		start_full_monitor(philo);
	while (waitpid(-1, NULL, 0) > 0)
		;
	sem_close(args.forks_sem);
	sem_close(args.full_sem);
	sem_close(args.death_sem);
	return (0);
}
