/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:09:53 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/04 17:10:27 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit = 0;

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	if (ac > 1)
		exit(EXIT_FAILURE);
	data.env = envcp(envp);
	data.root = NULL;
	data.exec = 0;
	set_attribute();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	singleton(&data);
	while (1)
		get_cmd(&data);
	return (0);
}
