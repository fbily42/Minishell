/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:45:32 by sbeylot           #+#    #+#             */
/*   Updated: 2022/10/26 09:50:50 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
