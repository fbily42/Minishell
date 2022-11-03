/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:00:33 by fbily             #+#    #+#             */
/*   Updated: 2022/11/03 19:59:18 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
Find the line "PATH=" in (char **)envp
Split every paths between " : "
Call create_paths
Return : TRUE if everything is OK
Return : FALSE if something wrong happened.
*/
bool	find_paths(t_context *ctx)
{
	char	*path;
	int		i;

	i = 0;
	while (ctx->envp[i])
	{
		path = ft_strnstr(ctx->envp[i], "PATH=", 5);
		if (path)
		{	
			path = ft_substr(ctx->envp[i], 5, ft_strlen(ctx->envp[i]));
			if (!path)
				return (false);
			break ;
		}
		i++;
	}
	if (!path)
		return (true);
	ctx->my_paths = ft_split(path, ":");
	free(path);
	if (!*ctx->my_paths)
		return (false);
	if (create_paths(ctx) == false)
		return (false);
	return (true);
}

/* 
Create every paths and store them in (char **)ctx.my_paths
Return : TRUE if everything is OK
Return : FALSE if something wrong happened.
*/
bool	create_paths(t_context *ctx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ctx->my_paths[j])
		j++;
	while (ctx->my_paths && ctx->my_paths[i])
	{
		ctx->my_paths[i] = strjoin_and_free_s1(ctx->my_paths[i], "/");
		if (ctx->my_paths[i] == NULL)
		{
			i = 0;
			while (i < j)
				free(ctx->my_paths[i++]);
			free(ctx->my_paths);
			ctx->my_paths = NULL;
			return (false);
		}
		i++;
	}
	return (true);
}

/* 
Split argv to have the command and his options
Store if in (char **)vars.options
Check if this command is valid
If not, call check_path_cmd
Return : TRUE if everything is OK
Return : FALSE if something wrong happened.
*/
bool	find_cmd(t_node *tree, t_context *ctx)
{
	if (access(tree->data.c.value[0], F_OK | X_OK) == 0)
	{
		ctx->cmd = ft_strdup(tree->data.c.value[0]);
		if (ctx->cmd == NULL)
			return (false);
		return (true);
	}
	if (*ctx->envp != NULL && ctx->my_paths != NULL)
	{
		if (error_msg(ctx, tree->data.c.value[0]) == false)
			return (false);
		if (check_path_cmd(ctx, tree) == true)
			return (true);
	}
	print_error_cmd(ctx, tree->data.c.value[0]);
	return (false);
}

/* 
Test the command with every paths.
Return : TRUE if command is OK
Return : FALSE if something wrong happened or command not found.
*/
bool	check_path_cmd(t_context *ctx, t_node *tree)
{
	int	i;

	i = 0;
	while (ctx->my_paths[i])
	{
		ctx->cmd = ft_strjoin(ctx->my_paths[i], tree->data.c.value[0]);
		if (ctx->cmd == NULL)
			return (false);
		if (access(ctx->cmd, F_OK | X_OK) == 0
			&& ((tree->data.c.value[0][0] == '.'
				&& tree->data.c.value[0][1] == '/')
					|| tree->data.c.value[0][0] == '/'))
		{
			perror(ctx->error);
			clean_struct(ctx);
			exit(127);
		}
		else if (access(ctx->cmd, F_OK | X_OK) == 0)
			return (true);
		else
			free (ctx->cmd);
		i++;
	}
	ctx->cmd = NULL;
	return (false);
}

/*
Search if the command exist and try to execute it.
*/
void	execute_cmd(t_node *tree, t_context *ctx)
{
	if (find_cmd(tree, ctx) == true)
	{
		execve(ctx->cmd, tree->data.c.value, ctx->envp);
		perror("Execve ");
		clean_struct(ctx);
		exit(126);
	}
	else
	{
		clean_struct(ctx);
		exit(127);
	}
}
