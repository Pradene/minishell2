/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:55:00 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/17 20:55:22 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	prerror(char *msg)
{
	write(2, msg, ft_strlen(msg));
}
