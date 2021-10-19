/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:32:48 by artmende          #+#    #+#             */
/*   Updated: 2021/10/09 15:33:00 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	i;
	char			temp[10];

	if (!n)
		write(fd, "0", 1);
	if (n < 0)
		write(fd, "-", 1);
	i = 0;
	while (n)
	{
		if (n > 0)
			temp[i++] = (n % 10) + '0';
		else
			temp[i++] = -(n % 10) + '0';
		n = n / 10;
	}
	while (i--)
		write(fd, &temp[i], 1);
}
