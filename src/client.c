/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalch <akovalch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:41:29 by akovalch          #+#    #+#             */
/*   Updated: 2025/02/25 14:39:40 by akovalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include "../includes/errors.h"

volatile sig_atomic_t	g_received = 0;

void	acknowledge_sig(int signum)
{
	(void)signum;
	g_received = 1;
}

void	sig_killer(pid_t pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_received = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_received)
			usleep(50);
		usleep(50);
		i--;
	}
}

void	initialize_sigaction(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){0};
	sa.sa_handler = acknowledge_sig;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(int argc, char *argv[])
{
	pid_t				pid;
	char				*str;

	if (argc != 3)
		return (ft_printf(ERR_ARG), 1);
	ft_printf("__PID: %d\n", getpid());
	pid = ft_atoi(argv[1]);
	str = argv[2];
	if (pid <= 0)
		return (ft_printf(ERR_PID), 1);
	
	initialize_sigaction();
	while (*str)
	{
		sig_killer(pid, (unsigned char)*str);
		str++;
	}
	sig_killer (pid, '\0');
	return (0);
}
