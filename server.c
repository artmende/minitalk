/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:18:11 by artmende          #+#    #+#             */
/*   Updated: 2021/10/16 15:48:59 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	When the server launches, it displays its PID, so the client can send a
**	message to it. It then stays in a infinite loop waiting to receive signals.
**
**	When a signal is received, it launches the handler function, and it has to
**	be launched again and again for each signal received. As no custom parameter
**	can be passed to the handler function, we have to use global or static
**	variables to keep value between the calls of handler.
**
**	The data that we need are :
**	- the number of signals (the first 32 signals are the string length)
**	- the string length
**	- a pointer so we can allocate memory for the string, and then free it
**	- an index to be able to browse the allocated memory
**
**	Using bitwise operation, we first reconstituate the string length, then we 
**	allocate memory for the string, and we reconsituate each characters and
**	store them.
**	After receiving as many characters as the length, we display the string and
**	we free the allocated memory and reset all static variables to zero.
*/

#include "minitalk.h"

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
	{
		sigaction(SIGUSR2, &sa, NULL);
		sigaction(SIGUSR1, &sa, NULL);
		pause();
	}
	return (0);
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static t_server_data	data = {0, 0, 0, 0};

	(void)sig;
	(void)context;
	if (data.nbr_of_signals < 32)
		return (receive_length(info, &data));
	if (data.len)
		return (receive_message(info, &data));
}

/*
**	receive_length :
**
**	Bitwise operations are endianness independant.
**
**	We have to receive an unsigned int.
**	We use the mask 00000000 00000000 00000000 00000001
**
**	If we receive a 1, we set the right most bit of data->len to 1 by doing a
**	bitwise OR.
**	If we receive a 0, we leave the right most bit to its default value (0).
**	Then, after receiving a signal (except for the last one), we left shift
**	data->len
**
**	When the length has been received, we allocate the right amount of memory.
*/

void	receive_length(siginfo_t *info, t_server_data *data)
{
	unsigned int	mask;

	data->nbr_of_signals++;
	mask = 1;
	if (info->si_signo == SIGUSR1)
		data->len = data->len | mask;
	if (data->nbr_of_signals < 32)
		data->len = data->len << 1;
	else
	{
		data->str = ft_calloc(sizeof(char) * (data->len + 1), 1);
		if (!data->str)
			exit(EXIT_FAILURE);
	}
}

/*
** receive_message :
**
**	Each character is represented by 8 signals.
**
**	We use a mask (00000001) to reconstituate each char like we did with the
**	string length. We can directly use the 0 from calloc to shift and OR to 
**	reconstituate the original char.
**
**	After 8 signals received, we go to the next allocated byte, until we reach
**	the end.
**
**	When all the message has been received, we display the string, free the 
**	memory and reset the static variables.
*/

void	receive_message(siginfo_t *info, t_server_data *data)
{
	unsigned char	mask;

	data->nbr_of_signals++;
	mask = 1;
	if (info->si_signo == SIGUSR1)
		data->str[data->index] = data->str[data->index] | mask;
	if (data->nbr_of_signals % 8)
		data->str[data->index] = data->str[data->index] << 1;
	else
	{
		data->index++;
		data->len--;
	}
	if (!data->len)
	{
		write(1, data->str, ft_strlen((char *)data->str));
		write(1, "\n", 1);
		free(data->str);
		ft_memset(data, 0, sizeof(t_server_data));
		kill(info->si_pid, SIGUSR2);
	}
}
