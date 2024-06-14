/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_listutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 15:52:33 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg	*ft_stacklast(t_arg *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	append_node(t_arg **lst, char *str, t_append info, int value)
{
	t_arg	*node;

	if (!lst)
		return ;
	node = ft_calloc(1, sizeof(t_arg));
	if (!node)
		return ;
	node->next = NULL;
	node->str = ft_substr(str, info.start, info.len);
	if (!node->str) 
	{
		free(node);
		return ;
	}
	node->type = value;
	connect_last(&node, lst);
}
