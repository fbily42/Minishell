/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:42:23 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/06 19:30:57 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		}
		else if (info->si_pid == 0)
		{
			write(1, "\n", 1);
			g_minishell_exit = 130;
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
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
