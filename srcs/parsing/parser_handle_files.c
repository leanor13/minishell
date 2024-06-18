/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/10 20:01:54 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_syntax_error(t_arg **lst, t_arg **node, t_arg **temp_lst)
{
	ft_printsyntaxerror(lst);
	free_args(node);
	free_args(temp_lst);
}

void	handle_heredoc(t_arg **lst, t_heads *heads, \
t_arg **node, t_arg **temp_lst)
{
	if ((*lst)->next == NULL)
	{
		*lst = (*lst)->next;
		return ;
	}
	if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT || \
		(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND || \
		(*lst)->next->type == PIPE)
	{
		handle_syntax_error(lst, node, temp_lst);
		return ;
	}
	*lst = (*lst)->next;
	heads->i++;
	(*lst)->type = GOING_HEREDOC;
}

void	handle_output(t_arg **lst, t_heads *heads, \
t_arg **node, t_arg **temp_lst)
{
	if ((*lst)->next == NULL)
	{
		*lst = (*lst)->next;
		return ;
	}
	if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT || \
		(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND || \
		(*lst)->next->type == PIPE)
	{
		handle_syntax_error(lst, node, temp_lst);
		return ;
	}
	*lst = (*lst)->next;
	heads->k++;
	(*lst)->type = GOING_OUTPUT;
}

void	handle_input(t_arg **lst, t_heads *heads, \
t_arg **node, t_arg **temp_lst)
{
	if ((*lst)->next == NULL)
	{
		*lst = (*lst)->next;
		return ;
	}
	if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT || \
		(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND || \
		(*lst)->next->type == PIPE)
	{
		handle_syntax_error(lst, node, temp_lst);
		return ;
	}
	*lst = (*lst)->next;
	heads->l++;
	(*lst)->type = GOING_INPUT;
}

void	handle_append(t_arg **lst, t_heads *heads, \
t_arg **node, t_arg **temp_lst)
{
	if ((*lst)->next == NULL)
	{
		*lst = (*lst)->next;
		return ;
	}
	if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT || \
		(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND || \
		(*lst)->next->type == PIPE)
	{
		handle_syntax_error(lst, node, temp_lst);
		return ;
	}
	(*node)->append = true;
	*lst = (*lst)->next;
	heads->k++;
	(*lst)->type = GOING_OUTPUT;
}
