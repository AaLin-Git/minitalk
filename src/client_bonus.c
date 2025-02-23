/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalch <akovalch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:41:29 by akovalch          #+#    #+#             */
/*   Updated: 2025/02/23 19:52:28 by akovalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

volatile sig_atomic_t	received = 0;

void acknowledge_sig(int signum)
{
	(void)signum;
	received = 1;
}

void	sig_killer(pid_t pid, unsigned char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		received = 0;
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!received)
			usleep(100);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	char	*str;
	struct sigaction sa;

	if (argc != 3)
	{
		ft_printf("Use only 3 arguments...\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	if (pid <= 0)
	{
		ft_printf("PID is wrong");
		return (1);
	}
	sa = (struct sigaction){0};
	sa.sa_handler = acknowledge_sig;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	while (*str)
	{
		sig_killer(pid, (unsigned char)*str);
		str++;
	}
	sig_killer (pid, '\0');
	pause();
	return (0);
}