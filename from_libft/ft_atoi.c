/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:30:52 by artmende          #+#    #+#             */
/*   Updated: 2021/10/13 18:52:41 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

/*
	ft_atoi has been modified a little bit to look for int overflows.
*/

int	ft_atoi(const char *str)
{
	long int	result_l;
	int			minus;
	int			i;

	result_l = 0;
	minus = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '-' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (i > 0 && str[i - 1] == '-')
		minus = -1;
	i = 0;
	while (*str == ' ' || *str == '-' || (*str >= 9 && *str <= 13))
		str++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result_l = 10 * result_l + str[i] - '0';
		i++;
	}
	if (i > 10 || (i == 10 && *str > '2')
		|| (minus == 1 && result_l > 2147483647)
		|| (minus == -1 && result_l > 2147483648))
		return (0);
	return ((int)(minus * result_l));
}
