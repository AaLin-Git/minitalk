/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalch <akovalch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:41:46 by akovalch          #+#    #+#             */
/*   Updated: 2025/02/25 12:16:11 by akovalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	sighandler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				i;

	(void)context;
	if (signum == SIGUSR1)
		c = (c << 1);
	else if (signum == SIGUSR2)
		c = (c << 1) | 1;
	i++;
	if (i == 8)
	{
		if (c == 0)
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		i = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void sighandler_kill(int signum)
{
	(void)signum;
	exit(0);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", getpid());
	sa = (struct sigaction){0};
	sa.sa_sigaction = sighandler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction (SIGUSR1, &sa, NULL);
	sigaction (SIGUSR2, &sa, NULL);

	struct sigaction	sa1;
	sa1 = (struct sigaction){0};
	sa1.sa_handler = sighandler_kill;
	sigaction (SIGINT, &sa1, NULL);
	
	while (1)
		pause();
	return (0);
}
