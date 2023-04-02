/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:34:43 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/26 23:34:47 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**export(char **env, char *new)
{
	int		c;
	char	**e;

	c = -1;
	while (env[++c])
		continue ;
	e = malloc(sizeof(char *) * (c + 1 + 1));
	if (!e)
		return (env);
	e[c + 1] = NULL;
	c = -1;
	while (env[++c])
	{
		e[c] = ft_strdup(env[c]);
		if (!e[c])
			return (d_free(e), env);
	}
	e[c] = ft_strdup(new);
	if (!e[c])
		return (d_free(e), env);
	d_free(env);
	return (e);
}
