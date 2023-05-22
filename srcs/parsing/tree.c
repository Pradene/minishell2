/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:20:33 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/05 19:20:34 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(t_node *node)
{
	int	i;

	if (!node->cmd)
		return ;
	i = -1;
	while (node->cmd[++i])
		free(node->cmd[i]);
	free(node->cmd);
}

void	free_node(t_node *node)
{
	if (!node || node->type == ERR)
		return ;
	else if (node->type == CMD)
		free_cmd(node);
	else if (node->type == R_IN || node->type == HEREDOC \
	|| node->type == R_OUT || node->type == R_OUT2)
		free(node->file);
	if (node->fd_in != -1)
		close(node->fd_in);
	if (node->fd_out != -1)
		close(node->fd_out);
	if (node->right)
		free_node(node->right);
	if (node->left)
		free_node(node->left);
	free(node);
}

void	print_cmd(char **cmds)
{
	int	i;

	if (!cmds)
		return ;
	i = -1;
	printf("CMDS: ");
	while (cmds[++i])
		printf("%s ", cmds[i]);
	printf("\n");
}

void	print_redir(t_node *node)
{
	if (node->type == R_OUT)
		printf("> ");
	else if (node->type == R_OUT2)
		printf(">> ");
	else if (node->type == R_IN)
		printf("< ");
	else if (node->type == R_OUT2)
		printf("HEREDOC: ");
	printf("%s\n", node->file);
}

void	print_node(t_node *node)
{
	if (node->type == ERR)
		printf("ERR\n");
	else if (node->type == CMD)
		print_cmd(node->cmd);
	else if (node->type == R_OUT || node->type == R_OUT2 \
	|| node->type == R_IN || node->type == HEREDOC)
		print_redir(node);
	else if (node->type == PIPE)
		printf("PIPE\n");
	else if (node->type == DBL_PIPE)
		printf("DBL_PIPE\n");
	else if (node->type == AMP)
		printf("AMP\n");
	else if (node->type == DBL_AMP)
		printf("DBL_AMP\n");
	else if (node->type == SEMICOL)
		printf("SEMICOL\n");
	else if (node->type == OPEN_BRACKET)
		printf("OPEN_BRACKET\n");
	else if (node->type == CLOSE_BRACKET)
		printf("CLOSE_BRACKET\n");
}

void	print_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->type == OPEN_BRACKET)
		print_node(node);
	print_tree(node->left);
	if (node->type != OPEN_BRACKET)
		print_node(node);
	print_tree(node->right);
}
