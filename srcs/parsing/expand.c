/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:13:47 by tmalless          #+#    #+#             */
/*   Updated: 2023/06/28 15:58:22 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_index(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			break ;
	}
	return (i);
}

char	*handle_dollar(t_data *data, char *cmd, int status, int *c)
{
	int		i;
	int		size;
	char	*value;
	char	*key;

	i = 0;
	key = NULL;
	value = NULL;
	while (cmd[++i])
	{
		if (ft_isalnum(cmd[i]) || cmd[i] == '_')
		{
			size = get_index(&cmd[i]);
			key = ft_strndup(&cmd[i], size);
			value = get_env(data->env, key);
			free(key);
			(*c) += size;
			return (value);
		}
		else if (status == 2 && cmd[i] == '\"')
			return ("$");
		else
			break ;
	}
	return (NULL);
}

void	handle_exit_status(char **new)
{
	char	*tmp;

	tmp = ft_itoa(g_exit);
	if (!tmp)
		return ;
	*new = ft_stradd(*new, tmp);
	free(tmp);
}

char	*expansion(t_data *data, char *cmd)
{
	char	*new;
	char	*tmp;
	int		quotes;
	int		i;

	i = -1;
	quotes = 0;
	new = NULL;
	tmp = NULL;
	while (cmd && cmd[++i])
	{
		quote_status(cmd[i], &quotes);
		if (quotes != 1 && cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] == '?')
			(handle_exit_status(&new), i += 1);
		else if (quotes != 1 && cmd[i] == '$' && cmd[i + 1])
		{
			tmp = handle_dollar(data, &cmd[i], quotes, &i);
			new = ft_stradd(new, tmp);
		}
		else
			new = ft_addchar(new, cmd[i]);
	}
	return (free(cmd), new);
}

char	**expand(t_data *data, char **cmds)
{
	int		i;
	int		j;
	char	*tmp;

	if (!data->env || !cmds)
		return (NULL);
	i = -1;
	j = -1;
	while (cmds[++i])
	{
		tmp = ft_strdup(cmds[i]);
		cmds[++j] = expansion(data, cmds[i]);
		if (!cmds[j] && tmp)
			j -= 1;
		free(tmp);
	}
	cmds[++j] = NULL;
	return (cmds);
}
