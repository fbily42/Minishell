/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:42:23 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/18 12:19:26 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

extern int	g_minishell_exit;

void	handle_sigint(int signum, siginfo_t *info, void *i)
{
	(void)i;
	if (signum == SIGINT)
	{
		if (info->si_pid > 0)
		{
			rl_replace_line("", 0);
			write(1, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
			g_minishell_exit = 130;
		}
		else if (info->si_pid == 0)
		{
			write(1, "\n", 1);
			g_minishell_exit = 130;
		}
	}
}

void	handler_quit_child(int signum, siginfo_t *info, void *i)
{
	(void)i;
	if (signum == SIGQUIT)
	{
		if (info->si_pid == 0)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
			g_minishell_exit = 131;
		}
		else
		{
			write(1, "\b \b", 3);
			write(1, "\b \b", 3);
		}
	}
}

void	init_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int = (struct sigaction){0};
	sa_int.sa_sigaction = &handle_sigint;
	sa_int.sa_flags = SA_SIGINFO;
	sa_quit = (struct sigaction){0};
	sa_quit.sa_sigaction = &handler_quit_child;
	sa_quit.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
