/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:35:30 by artmende          #+#    #+#             */
/*   Updated: 2021/10/09 15:35:39 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ret;
	char			*ret_e;
	unsigned int	i;

	i = nmemb * size;
	ret = malloc(i);
	if (!ret)
		return (NULL);
	ret_e = (char *)ret;
	while (i)
	{
		ret_e[i - 1] = 0;
		i--;
	}
	return (ret);
}
