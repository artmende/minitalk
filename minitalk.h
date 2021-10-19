/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:18:20 by artmende          #+#    #+#             */
/*   Updated: 2021/10/16 17:52:11 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>

# define SLEEP_TIME 100

typedef struct s_server_data
{
	unsigned int	nbr_of_signals;
	unsigned int	len;
	unsigned int	index;
	unsigned char	*str;
}	t_server_data;

int		call_exit(void);

/*
**	client.c
*/

void	check_input(int argc, char *pid);
void	send_len_to_server(int pid_server, unsigned int len);
void	send_message_to_server(int pid_server, char *str);
void	confirmation_message_received(int sig, siginfo_t *info, void *context);

/*
**	server.c
*/

void	handler(int sig, siginfo_t *info, void *context);
void	receive_length(siginfo_t *info, t_server_data *data);
void	receive_message(siginfo_t *info, t_server_data *data);

/*
**	from_libft
*/

int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putnbr_fd(int n, int fd);

#endif
