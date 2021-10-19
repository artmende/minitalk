/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:33:37 by artmende          #+#    #+#             */
/*   Updated: 2021/10/09 15:33:49 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	c_e;
	unsigned char	*edit;

	c_e = (unsigned char)c;
	edit = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		edit[i] = c_e;
		i++;
	}
	return (s);
}
