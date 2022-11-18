/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:10:43 by fbily             #+#    #+#             */
/*   Updated: 2022/11/18 23:46:47 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all_tab(char **array, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(array[i++]);
	free(array);
}

static bool	swap_string(char **array, int index1, int index2)
{
	char	*tmp;
	int		len;

	len = tab_len(array);
	tmp = ft_strdup(array[index1]);
	if (!tmp)
		return (free_all_tab(array, len), false);
	free(array[index1]);
	array[index1] = ft_strdup(array[index2]);
	if (!array[index1])
		return (free_all_tab(array, len), false);
	free(array[index2]);
	array[index2] = ft_strdup(tmp);
	if (!array[index2])
		return (free_all_tab(array, len), false);
	free(tmp);
	return (true);
}

static void	add_prefixe(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		array[i] = strjoin_and_free_s2("declare -x ", array[i]);
		i++;
	}
}

static void	sort_env(t_context *ctx, char **sorted)
{
	int	size;
	int	i;
	int	j;

	i = 0;
	size = tab_len(ctx->envp);
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
			{
				if (swap_string(sorted, j, j + 1) == false)
					error_malloc(ctx);
			}
			j++;
		}
		i++;
	}
}

void	sort_and_print_env(t_context *ctx)
{
	char	**sorted;

	sorted = copy_env(ctx->envp);
	if (!sorted)
		error_malloc(ctx);
	sort_env(ctx, sorted);
	add_prefixe(sorted);
	if (ctx->pipe[STDOUT_FILENO] > 2)
		env(sorted, ctx->pipe[STDOUT_FILENO]);
	else
		env(sorted, STDOUT_FILENO);
	free_2d(sorted);
}
