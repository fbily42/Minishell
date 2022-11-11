/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:01:41 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/11 21:19:35 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_minishell_exit;

int	main(int argc, char **argv, char **envp)
{
	t_node		*tree;
	t_context	ctx;

	(void)argc;
	(void)argv;
	tree = NULL;
	if (isatty(STDIN_FILENO) == 0)
	{
		perror("PopCornShell ");
		return (1);
	}
	g_minishell_exit = 0;
	if (*envp)
		ctx.envp = copy_env(envp);
	else
		ctx.envp = handle_mini_envp(&ctx);
	init_signal();
	minishell(tree, &ctx);
	free_2d(ctx.envp);
	return (0);
}

void	minishell(t_node *tree, t_context *ctx)
{
	char		*line;

	line = NULL;
	while (1)
	{
		line = readline("🍿PopCornShell>> ");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		else if (*line && line[0])
			add_history(line);
		tree = parsing(line, ctx);
		exec(tree, ctx);
		clean_tree(&tree);
		free(line);
	}
}

char	**handle_mini_envp(t_context *ctx)
{
	char	dir[PATH_MAX];
	char	*pwd;

	ctx->envp = malloc(sizeof(char *));
	if (!*ctx->envp)
	{
		ft_putstr_fd("Error malloc\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	*ctx->envp = NULL;
	if (getcwd(dir, sizeof(dir)) == NULL)
		perror("Getcwd ");
	pwd = ft_strjoin("PWD=", dir);
	if (!pwd)
	{
		ft_putstr_fd("Error malloc\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ctx->envp = export(ctx->envp, pwd);
	if (!*ctx->envp)
	{
		ft_putstr_fd("Error malloc\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (ctx->envp);
}
