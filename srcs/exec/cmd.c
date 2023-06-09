/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:11:08 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/30 22:19:56 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_quotes(char *s)
{
	int	i;
	int	status;

	if (!s)
		return (0);
	i = -1;
	status = 0;
	while (s[++i])
	{
		if (!status && s[i] == '\"')
			status = 2;
		else if (!status && s[i] == '\'')
			status = 1;
		else if ((status == 1 && s[i] == '\'')
			|| (status == 2 && s[i] == '\"'))
			status = 0;
	}
	if (status == 2)
		prerror("syntax error, expected \'\"\'\n");
	if (status == 1)
		prerror("syntax error, expected \'\'\'\n");
	return (status);
}

void	get_cmd(t_data *data)
{
	char	*s;

	s = readline("minishell > ");
	if (!s)
	{
		printf("exit\n");
		dfree(data->env);
		exit(g_exit);
	}
	add_history(s);
	if (check_quotes(s))
		return (free(s));
	parse(data, &data->root, &s);
	data->c_heredoc = 0;
	data->parse = 1;
	data->exec = 1;
	exec(data, data->root);
	data->exec = 0;
	free_node(&data->root);
	lclear(&data->tmp);
	free(s);
}
