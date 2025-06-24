/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:45:01 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/24 17:07:09 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include "philosophers_bonus.h"

void	clean_philo(t_philo *philo)
{
	sem_close(philo->args->forks_sem);
	sem_close(philo->args->stop_sem);
	free(philo->args);
	free(philo);
}
