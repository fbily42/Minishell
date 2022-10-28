/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_simon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:01:41 by sbeylot           #+#    #+#             */
/*   Updated: 2022/10/27 20:06:54 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_minishell_env;

int buildin_echo_simple(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		i++;
		if (cmd[i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	ft_putendl_fd("", 1);
	return (1);
}

int	buildin_echo_option(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		i++;
		if (cmd[i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	return (1);
}

int  buildin_echo(char **cmd)
{
	int		i;

	i = 0;
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd[1], "-n") == 0)
		return (buildin_echo_option(cmd));
	else
		return (buildin_echo_simple(cmd));
}

void	execute_simple_cmd(t_node *node)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (execve(node->data.c.value[0], node->data.c.value, g_minishell_env) == -1)
		{
			printf("Fail\n");
			exit(20);
		}
	}
	else
	{
		waitpid(pid, &wstatus, 0);
		printf("J'ai bien execute la commande\n");
	}
}

void	visit(t_node *tree, int value)
{
	if (!tree)
		return ;
	if (tree->type == CMD)
	{
		if (value == 0)
			printf("Je Fork()\n");
		printf("Je fais une Commande\n");
		return ;
	}
	if (tree->type == REDIR && value == 0)
	{
		printf("Je Fork()\n");
		value = 1;
	}
	if (tree->type == REDIRIN || tree->type == REDIROUT)
	{
		printf("Je redirige\n");
		return ;
	}
	if (tree->type == PIPE)
		value = 0;
	printf("Je vais a Gauche\n");
	visit(tree->data.b.left, value);
	printf("Je vais a Droite\n");
	visit(tree->data.b.right, value);
	printf("Je remonte\n");
}

int	main(int argc, char **argv, char **envp)
{
	/* --- FT_MALLOCATOR TEST -----------------------------------
	//char	line[] = "echo -n \"COUCOU\" 2>File | cat File << ok ";
	(void)argc;
	(void)argv;
	g_minishell_env = envp;

	char	line_cmd[] = "<I <OOO /bin/echo Simon Beylot >O Pascaline | grep Simon | wc -l >ok";
	t_token *tokens;
	t_node	*tree;

	printf("Command:[%s]\n", line_cmd);
	tokens = NULL;
	tokenizer(line_cmd, &tokens);
	if (tokens)
	{
		tree = parse_redir(&tokens);
		if (!tree)
		{
			free_token(&tokens);
			return (1);
		}
		tree_print(tree);
	//	visit(tree);
	}
	clean_tree(&tree);
	free_token(&tokens);
	------ FT_MALLOCATOR TEST -------------------------------- */

	/* --- TEST EXPANSION --------------------------------------
	(void)argc;
	(void)argv;
	g_minishell_env = envp;
	char test[] = "Coucou $COLORTERM$PATH";
	char	*ok;
	ok = (char *)malloc(sizeof(char) * ft_strlen(test) + 1);
	if (!ok)
		return (1);
	size_t i;
	for (i = 0; i < ft_strlen(test);i++)
		ok[i] = test[i];
	ok[i] = '\0';
	char	*result = word_expansion(&ok);
	printf("%s\n", result);
	free(result);
	------ TEST EXPANSION ------------------------------------ */

	/* --- TOKEN ------------------------------------------------
	(void)argc;
	(void)argv;
	char	*line;
	t_token	*token;
	t_node	*test;
	g_minishell_env = envp;
	test = NULL;
	token = NULL;
	while (1)
	{
		line = readline("Test:> ");
		if (line == NULL)
			break ;
		else if (*line && line[0])
			add_history(line);
		tokenizer(line, &token);
		test = node_cmd(&token, NULL);
		print_node_cmd(test);
		printf("\n");
		token_print(token);
	}
	------ TOKEN --------------------------------------------- */
	/* --- MAIN -------------------------------------------------
	------ MAIN ---------------------------------------------- */
	char	*line;
	t_node	*tree;

	(void)argc;
	(void)argv;
	g_minishell_env = envp;
	line = NULL;
	tree = NULL;
	init_signal();
	while (1)
	{
		line = readline("🍿PopCornshell >> ");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		else if (*line && line[0])
			add_history(line);
		tree = parsing(line);
		tree_print(tree);
		visit(tree, 0);
		clean_tree(&tree);
		free(line);
	}
	return (0);
}
