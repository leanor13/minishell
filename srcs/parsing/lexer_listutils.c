/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_listutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/31 15:53:21 by thuy-ngu         ###   ########.fr       */
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

void	free_stackfinal(t_arg **lst)
{
	t_arg	*tmp;
	t_arg	*current;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*lst = NULL;
}

void	append_node(t_arg **lst, char *str, t_append info, int value)
{
	t_arg	*node;
	t_arg	*nlast;

	if (!lst)
		return ;
	node = malloc(sizeof(t_arg));
	if (!node)
		return ;
	node->next = NULL;
	node->str = ft_substr(str, info.start, info.len);
	node->type = value;
	if (!(*lst))
	{
		*lst = node;
		node->prev = NULL;
	}
	else
	{
		nlast = ft_stacklast(*lst);
		nlast->next = node;
		node->prev = nlast;
	}
}
