/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ifutils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 15:49:05 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	if_strjoin(t_heads heads, t_arg **node, t_shell *shell)
{
	if (heads.i != 0)
		(*node)->here_doc = ft_strjoin_heredoc(heads.head_heredoc, heads.i);
	if (heads.j != 0)
		(*node)->arguments = ft_strjoin_args(heads.head_arg, heads.j, shell);
	if (heads.k != 0)
		(*node)->out_file = ft_strjoin_output(heads.head_output, heads.k);
	if (heads.l != 0)
		(*node)->in_file = ft_strjoin_input(heads.head_input, heads.l);
}

void	if_dollarsign(t_arg **lst, t_heads *heads)
{
	if ((*lst)->type == DOLLAR_SIGN)
	{
		heads->j++;
		(*lst)->type = GOING_DOLLAR_SIGN;
	}
	if ((*lst)->type == SINGLEQUOTE_DOLLAR)
	{
		heads->j++;
		(*lst)->type = GOING_SINGLEQUOTE_DOLLAR;
	}
	return ;
}

int	if_doublepipe(t_arg **lst, t_arg **node, t_arg **temp_lst)
{
	if ((*lst)->type == DOUBLE_PIPE)
	{
		ft_printsyntaxerror(lst);
		free_args(node);
		free_args(temp_lst);
		return (0);
	}
	return (1);
}

int	if_pipe(t_arg **lst, t_arg **node, t_arg **temp_lst)
{
	if ((*lst)->type == PIPE)
	{
		if ((*lst)->next == NULL)
		{
			*lst = (*lst)->next;
			return (0);
		}
		if ((*lst)->prev == NULL)
		{
			if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT || \
			(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND \
			|| (*lst)->next->type == PIPE)
			{
				ft_printsyntaxerror(lst);
				free_args(node);
				free_args(temp_lst);
				return (0);
			}
		}
		*lst = (*lst)->next;
		return (0);
	}
	return (1);
}
