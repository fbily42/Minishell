/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:45:32 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/12 14:07:43 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_minishell_exit;
/*
 * int dollar_inside(char *str)
 * @str:	string
 * ||	Check if a dollar is present in the string
 *
 * int tab_length(char **tab)
 * @tab:	Array of string
 * ||	Return the length of the array
 *
 * int	var_exist(char *str, char **envp)
 * @str:	String
 * @envp:	Shell Environment
 * ||	Check if the variable exist in the shell env
 *
 * int	word_expansion_len(char **tab)
 * @tab:	Array of string
 * || 	Return the length of the string with replace value
 */

int	dollar_inside(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (i);
	}
	return (-1);
}

int	tab_length(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

int	var_exist(char	*str, char **envp)
{
	int	i;

	i = -1;
	if (!envp)
		return (0);
	if (*str == '$')
		str++;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			return (1);
	}
	return (0);
}

int	word_expansion_len(char **tab)
{
	int		index;
	int		i;
	int		word_len;

	word_len = 0;
	index = -1;
	while (tab[++index])
	{
		i = -1;
		while (tab[index][++i])
			word_len++;
	}
	return (word_len);
}

void	we_create_word_utils(char **tab, int i, t_context *ctx, int tab_len)
{
	char	*copy;

	if (tab[i][0] == '$' && tab[i][1] == '?')
	{
		free(tab[i]);
		tab[i] = ft_itoa(g_minishell_exit);
	}
	else if (tab[i][0] == '$' && tab[i][1] != '\0')
	{
		copy = ft_strjoin(tab[i] + 1, "=");
		if (!copy)
			return (clean_tab(tab, tab_len));
		free(tab[i]);
		if (var_exist(copy, ctx->envp))
			tab[i] = get_path_env(ctx->envp, copy);
		else
			tab[i] = ft_strdup("");
		free(copy);
	}
}
