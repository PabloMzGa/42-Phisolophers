/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:04:13 by pablo             #+#    #+#             */
/*   Updated: 2025/06/26 13:04:47 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/**
 * @brief Sets the first n bytes of the memory area pointed to by s
 *        to the specified byte value c.
 *
 * This is a static implementation of the standard memset function.
 *
 * @param s Pointer to the memory area to be filled.
 * @param c Value to be set. The value is passed as an int, but the
 *        function fills the block of memory using the unsigned char
 *        conversion of this value.
 * @param n Number of bytes to be set to the value.
 * @return The original pointer s.
 */
static void	*ft_memset(void *s, int c, size_t n)
{
	char	*temp_s;
	char	byte;

	temp_s = (char *)s;
	byte = (char)c;
	while (n > 0)
	{
		*temp_s = byte;
		--n;
		++temp_s;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
