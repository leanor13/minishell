/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ifutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/10 20:32:23 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	if_util1(t_arg **lst, t_arg **node, t_arg **temp_lst, t_heads *heads)
{
	if ((*lst)->type == HEREDOC)
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
			ft_printsyntaxerror(lst);
			free_args(node);
			free_args(temp_lst);
			return (0);
		}
		*lst = (*lst)->next;
		heads->i++;
		(*lst)->type = GOING_HEREDOC;
	}
	else if ((*lst)->type == ARG)
	{
		heads->j++;
		(*lst)->type = GOING_ARG;
	}
	return (1);
}