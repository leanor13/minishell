/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ifutils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 15:05:48 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	if_pipe(t_arg **lst, t_arg **node, t_arg **temp_lst)
{
	if ((*lst)->type == PIPE)
	{
		if ((*lst)->next == NULL)
		{
			*lst = (*lst)->next;
			return (0);
		}
		if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT || \
		(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND \
		|| (*lst)->next->type == PIPE)
		{
			printf("ITT\n");
			ft_printsyntaxerror(lst);
			free_args(node);
			free_args(temp_lst);
			return (0);
		}
		*lst = (*lst)->next;
		return (0);
	}
	return (1);
}