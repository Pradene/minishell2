/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:55:34 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/28 13:04:13 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_handler(int sig)
{
	t_data	*data;

	(void)sig;
	data = singleton(NULL);
	if (!data)
		return ;
	printf("\n");
	if (!data->exec)
	{
		g_exit = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
