/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:01:41 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/02 20:19:58 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_minishell_env;

void	visit_redir(t_node *tree)
{
	if (!tree)
	{
		printf("[REDIR]\tIl n'y a plus de redirection\n");
		return ;
	}
	if (tree->type == APPEND || tree->type == REDIRIN || tree->type == REDIROUT || tree->type == HEREDOC)
	{
		printf("[REDIR]\tIl y a une redirection, je fait mon bail\n");
		return ;
	}
	printf("[REDIR]\tJe vais a gauche\n");
	visit_redir(tree->data.b.left);
	printf("[REDIR]\tJe vais droite\n");
	visit_redir(tree->data.b.right);
}

void	visit_cmd(t_node *tree)
{
	printf("[CMD]\tJe suis sur une commande [CMD]\n");
	if (tree->data.b.right == NULL)
		printf("[CMD]\tIl n'y a pas de redirection a droite, je vais a gauche\n");
	else if (tree->data.b.right)
	{
		printf("[CMD]\tIl y a une(des) redirection, je vais a droite\n");
		visit_redir(tree->data.b.right);
	}
	printf("[CMD]\tJ'execute la commande\n\n");
}

void	new_visit(t_node *tree)
{
	if (!tree)
		return ;
	if (tree->type == CMD)
	{
		visit_cmd(tree);
		return ;
	}
	if (tree->type == PIPE)
		printf("[PIPE]\tJe suis sur un pipe, je vais a gauche\n\n");
	new_visit(tree->data.b.left);
	printf("[PIPE]\tJ'ai execute a gauche, je vais a droite\n\n");
	new_visit(tree->data.b.right);
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
	(void)argc;
	(void)argv;
	char	*line;
	t_node	*tree;
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
		tree = new_parsing(line);
		tree_print(tree);
		new_visit(tree);
		clean_tree(&tree);
		free(line);
	}
	return (0);
}
