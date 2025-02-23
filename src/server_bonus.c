/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalch <akovalch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:41:46 by akovalch          #+#    #+#             */
/*   Updated: 2025/02/23 20:04:18 by akovalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	sighandler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				i;

	(void)context;
	if (signum == SIGUSR1)
		c |= 1 << i;
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
	usleep(100);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){0};
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = sighandler;
	ft_printf("PID: %d\n", getpid());
	sigaction (SIGUSR1, &sa, NULL);
	sigaction (SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
