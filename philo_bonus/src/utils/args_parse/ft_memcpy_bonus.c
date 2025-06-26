/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:49:48 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/26 13:01:26 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*temp_dest;
	const char	*temp_src;

	if (!dest && !src)
		return (NULL);
	temp_dest = (char *)dest;
	temp_src = (const char *)src;
	while (n--)
		*(temp_dest++) = *(temp_src++);
	return (dest);
}
