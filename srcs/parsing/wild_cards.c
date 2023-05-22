/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:55:58 by tmalless          #+#    #+#             */
/*   Updated: 2023/05/10 16:40:58 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**add_dir(char *s, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	tab[i] = s;
	return (tab);
}

char	**fill_motif(char *cmd, char **motif, int m_count)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (cmd[i] == '*')
		i++;
	while (k < m_count)
	{
		j = i;
		while (cmd[i] != '*')
			i++;
		motif[k] = ft_substr(cmd, j, i - j);
		k++;
		while (cmd[i] == '*')
			i++;
	}
	return (motif);
}

char	**create_motif(char *cmd, char **motif)
{
	int	i;
	int	m_count;

	i = 0;
	m_count = 0;
	while (cmd[i])
	{
		while (cmd[i] == '*')
			i++;
		if (cmd[i] && !ft_strchr(" \'\"", cmd[i]))
			m_count++;
		else
			break ;
		while (cmd[i] && cmd[i] != '*')
			i++;
	}
	motif = ft_calloc(sizeof(char *), m_count + 1);
	return (fill_motif(cmd, motif, m_count));
}

int	motif_size(char **motif)
{
	int	i;

	i = 0;
	if (!motif)
		return (0);
	while (motif[i])
		i++;
	return (i);
}

int	corresponding_dir(char *dir, char **motif, int stars)
{
	int		i;
	int		j;
	char	*k;

	i = 0;
	j = 0;
	if (!motif)
		return (1);
	if ((stars == 0 || stars == 2) && motif[0])
	{
		if (ft_strncmp(motif[0], dir, ft_strlen(motif[0])) != 0)
			return (0);
		else
		{
			i = ft_strlen(motif[0]) - 1;
			j = 1;
		}
	}
	while (j < motif_size(motif))
	{
		if (j == motif_size(motif) - 1 && (stars == 0 || stars == 1))
		{
			if (ft_strncmp(motif[motif_size(motif) - 1], &dir[ft_strlen(dir) - ft_strlen(motif[motif_size(motif) - 1])], ft_strlen(motif[motif_size(motif) - 1])) != 0)
				return (0);
			else
				return (1);
		}
		else
		{
			k = ft_strnstr(&dir[i], motif[j], ft_strlen(dir) - i);
			if (!k)
				return (0);
			else
			{
				dir = k + ft_strlen(motif[j]);
				j++;
				i = 0;
			}
		}
	}
	return (1);
}

int	handle_star(char *cmd)
{
	if (cmd[0] != '*' && cmd[ft_strlen(cmd) - 1] != '*')
		return (0);
	else if (cmd[0] == '*' && cmd[ft_strlen(cmd) - 1] != '*')
		return (1);
	else if (cmd[0] != '*' && cmd[ft_strlen(cmd) - 1] == '*')
		return (2);
	else
		return (3);
}

char	**wild_carder(char *cmd)
{
	struct dirent	*lecture;
	DIR				*rep;
	char			**ans;
	char			**motif;
	static int		d_number = 0;

	motif = NULL;
	rep = NULL;
	motif = create_motif(cmd, motif);
	rep = opendir(".");
	ans = ft_calloc(sizeof(char *), 4096);
	if (!ans)
		return (NULL);
	lecture = readdir(rep);
	while (lecture)
	{
		if (d_number > 4095)
			break ;
		if (corresponding_dir(lecture->d_name, motif, handle_star(cmd)))
		{
			add_dir(lecture->d_name, ans);
			d_number++;
		}
		lecture = readdir(rep);
	}
	//closedir(rep);
	dfree(motif);
	return (ans);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	cmd_nbrs(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

char	**wild_card(char **cmds, int i, int j, int k)
{
	int		n;
	char	**new_cmd;
	char	**old_cmd;
	char	**dirs;

	if (!cmds)
		return (cmds);
	old_cmd = cmds;
	while (old_cmd[i])
	{
		k = 0;
		j = 0;
		if (old_cmd[i] && ft_strchr(old_cmd[i], '*') && (!ft_strchr(old_cmd[i], '\'') && !ft_strchr(old_cmd[i], '\"')))
		{
			dirs = wild_carder(old_cmd[i]);
			if (dirs[0])
			{
				new_cmd = ft_calloc(tab_size(dirs) + tab_size(old_cmd) + 1, sizeof(char *));
				while (j < i)
				{
					new_cmd[j] = old_cmd[j];
					j++;
				}
				while (dirs[k])
				{
					new_cmd[j] = dirs[k];
					k++;
					j++;
				}
				free(dirs);
				n = i + 1;
				i = j - 1;
				while (old_cmd[n])
				{
					new_cmd[j] = old_cmd[n];
					j++;
					n++;
				}
				free(old_cmd);
				old_cmd = new_cmd;
			}
			else
				free(dirs);
		}
		i++;
	}
	return (old_cmd);
}
