/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:39:39 by pablo             #+#    #+#             */
/*   Updated: 2025/07/04 13:20:20 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

int	main(int argc, char *argv[])
{
	t_args		args;
	t_philo		*philo;
	pthread_t	full_monitor_id;

	char *test;

	test = malloc(4444);
	(void)test;

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
			   pthread_detach(full_monitor_id);
	   }
	printf("Iniciando en pid %i\n", getpid());
	philo = philo_start(&args);
	if (!philo)
	{
		while (waitpid(-1, NULL, 0) > 0)
			;
		close_args_sems(&args);
	}
	else
		clean_philos(philo);
	return (0);
}
