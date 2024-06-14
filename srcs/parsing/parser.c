/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 15:48:54 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_printsyntaxerror(t_arg **lst)
{
	if ((*lst)->type == DOUBLE_PIPE)
		ft_printf("minishell: syntax error near unexpected token `|'\n");
	else if ((*lst)->next->type == HEREDOC)
		ft_printf("minishell: syntax error near unexpected token `<<'\n");
	else if ((*lst)->next->type == OUTPUT)
		ft_printf("minishell: syntax error near unexpected token `>'\n");
	else if ((*lst)->next->type == INPUT)
		ft_printf("minishell: syntax error near unexpected token `<'\n");
	else if ((*lst)->next->type == APPEND)
		ft_printf("minishell: syntax error near unexpected token `>>'\n");
	else
		ft_printf("minishell: syntax error near unexpected token `|'\n");
}

void	initialize_heads(t_heads *heads, t_arg *lst)
{
	heads->head_arg = lst;
	heads->head_heredoc = lst;
	heads->head_output = lst;
	heads->head_input = lst;
	heads->i = 0;
	heads->j = 0;
	heads->k = 0;
	heads->l = 0;
}

void	more_parsing(t_arg **lst, t_arg **node, t_arg **temp_lst, \
t_heads *heads)
{
	while (*lst)
	{
		if (!if_heredoc(lst, node, temp_lst, heads))
			return ;
		if_arg(lst, heads);
		if (!if_output(lst, node, temp_lst, heads))
			return ;
		if (!if_input(lst, node, temp_lst, heads))
			return ;
		if (!if_append(lst, node, temp_lst, heads))
			return ;
		if_dollarsign(lst, heads);
		if (!if_doublepipe(lst, node, temp_lst))
			return ;
		if (!if_pipe(lst, node, temp_lst))
			return ;
		*lst = (*lst)->next;
	}
}

void	connect_last(t_arg **node, t_arg **final)
{
	t_arg	*nlast;

	if (!(*final))
	{
		(*final) = (*node);
		(*node)->prev = NULL;
	}
	else
	{
		nlast = ft_stacklast(*final);
		nlast->next = (*node);
		(*node)->prev = nlast;
	}
	return ;
}

t_arg	*ft_parser(t_arg *lst, t_shell *shell)
{
	t_arg	*node;
	t_arg	*temp_lst;
	t_heads	heads;
	t_arg	*final;

	final = NULL;
	temp_lst = lst;
	while (lst)
	{
		initialize_heads(&heads, lst);
		node = ft_calloc(1, sizeof(t_arg));
		if (!node)
		{
			free_args(&temp_lst);
			return (NULL);
		}
		more_parsing(&lst, &node, &temp_lst, &heads);
		if (!temp_lst)
			return (NULL);
		if_strjoin(heads, &node, shell);
		connect_last(&node, &final);
	}
	free_args(&temp_lst);
	return (final);
}
