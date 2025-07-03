/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:39:39 by pablo             #+#    #+#             */
/*   Updated: 2025/07/03 16:44:09 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

int	main(int argc, char *argv[])
{
	t_args	args;
	t_philo *philo;

	if (!check_args(argc, argv))
		return (1);
	if (set_args(&args, argc, argv))
		return (1);
	printf("Iniciando en pid %i\n", getpid());
	philo = philo_start(&args);
	if (!philo)
	{
		while (waitpid(-1, NULL, 0) > 0)
		;
		close_args_sems(&args);
	}
	else
	{
		printf ("Post a main_thread en id %i\n", philo->id);
		//sem_post(philo->main_thread_ended_sem);
		clean_philos(philo);
	}
	return (0);
}
