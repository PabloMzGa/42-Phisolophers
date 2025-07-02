/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sem_numbered_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:59:13 by pablo             #+#    #+#             */
/*   Updated: 2025/06/26 14:10:10 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

sem_t	*get_sem_numbered(char *name, unsigned int id, int value)
{
	char	*id_str;
	char	*full_name;
	sem_t	*sem;

	id_str = ft_uitoa(id);
	full_name = ft_strjoin(name, id_str);
	free (id_str);
	sem = sem_open(full_name, O_CREAT, 0644, value);
	if (sem == SEM_FAILED)
		return (free (full_name), NULL);
	sem_unlink(full_name);
	free (full_name);
	return (sem);
}
