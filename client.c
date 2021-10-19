/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:17:59 by artmende          #+#    #+#             */
/*   Updated: 2021/10/16 17:54:02 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	The client receives a string and the server PID as arguments.
**	It first sends the string length to the server. Then it sends each byte of
**	the string.
**	To send data to the server, the client uses two signals. 
**	SIGUSR1 represents a 1, and SIGUSR2 represents a 0.
**
**	The string length is stored as a unsigned int. So that's 32 signals to send
**	to the server. Then for each char of the string, it is 8 signals to send.
**
**	We determine the value of each bit (of the unsigned int or the char) by
**	doing a logical comparison with a mask and then left shifting.
**
**	Bitwise operations are endianness independant.
**
**	For example if the mask m is "10000000" and the char c is "01101001", the
**	expression (m & c) will be null, showing us that the first bit of c is 0.
**	(We send a SIGUSR2).
**	Then we left shift c to get "11010010" and now (m & c) will not be null,
**	which means the second bit of c is 1. (We send a SIGUSR1).
**
**	Using that way of transmitting data, signs of char are conserved and we can
**	send unicode character without problem.
**
**	After each signal sent, the client wait a small amount of time, to ensure
**	the server has finished processing it, before sending the next signal.
**
**	There is no need to send a string ending marker because the server knows the
**	length of the string.
*/

#include "minitalk.h"

int	main(int argc, char **argv)
{
	int					pid_server;
	unsigned int		len;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = confirmation_message_received;
	sigaction(SIGUSR2, &sa, NULL);
	check_input(argc, argv[1]);
	pid_server = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	if (!len)
		return (0);
	send_len_to_server(pid_server, len);
	send_message_to_server(pid_server, argv[2]);
	pause();
	return (0);
}

void	check_input(int argc, char *pid)
{
	if (argc != 3)
		exit(EXIT_FAILURE);
	if (ft_atoi(pid) == 0)
		exit(EXIT_FAILURE);
	while (pid && *pid)
	{
		if (*pid < 48 || *pid > 57)
			exit(EXIT_FAILURE);
		pid++;
	}
}

/*
**	2147483648 unsigned is 10000000 00000000 00000000 00000000
*/

void	send_len_to_server(int pid_server, unsigned int len)
{
	unsigned int	mask;
	int				i;

	mask = 2147483648;
	i = 32;
	while (i)
	{
		if (len & mask)
			(void)(kill(pid_server, SIGUSR1) == -1 &&
				write(1, "Bad PID\n", 8) && call_exit());
		else
			(void)(kill(pid_server, SIGUSR2) == -1 &&
				write(1, "Bad PID\n", 8) && call_exit());
		usleep(SLEEP_TIME);
		len = len << 1;
		i--;
	}
}

/*
**	128 unsigned is 10000000
*/

void	send_message_to_server(int pid_server, char *str)
{
	int				i;
	unsigned char	mask;

	mask = 128;
	while (str && *str)
	{
		i = 8;
		while (i)
		{
			if (*str & mask)
				(void)(kill(pid_server, SIGUSR1) == -1 &&
					write(1, "Bad PID\n", 8) && call_exit());
			else
				(void)(kill(pid_server, SIGUSR2) == -1 &&
					write(1, "Bad PID\n", 8) && call_exit());
			usleep(SLEEP_TIME);
			*str = *str << 1;
			i--;
		}
		str++;
	}
}

void	confirmation_message_received(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	write(1, "Message transmitted succesfully !\n", 34);
	exit(EXIT_SUCCESS);
}
