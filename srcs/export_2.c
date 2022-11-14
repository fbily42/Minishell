/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:10:43 by fbily             #+#    #+#             */
/*   Updated: 2022/11/14 14:28:52 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_string(char **array, int index1, int index2)
{
	char	*tmp;

	tmp = ft_strdup(array[index1]);
	free(array[index1]);
	array[index1] = ft_strdup(array[index2]);
	free(array[index2]);
	array[index2] = ft_strdup(tmp);
	free(tmp);
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

void	sort_and_print_env(t_context *ctx)
{
	char	**sorted;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = tab_len(ctx->envp);
	sorted = copy_env(ctx->envp);
	if (!sorted)
		error_malloc(ctx);
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
				swap_string(sorted, j, j + 1);
			j++;
		}
		i++;
	}
	add_prefixe(sorted);
	env(sorted, STDOUT_FILENO);
	free_2d(sorted);
}
