/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/31 16:35:21 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_printsyntaxerror(t_arg **lst)
{
	if((*lst)->type == DOUBLE_PIPE)
		ft_printf("minishell: syntax error near unexpected token `|'\n");
	else if((*lst)->next->type == HEREDOC)
		ft_printf("minishell: syntax error near unexpected token `<<'\n");
	else if((*lst)->next->type == OUTPUT)
		ft_printf("minishell: syntax error near unexpected token `>'\n");
	else if((*lst)->next->type == INPUT)
		ft_printf("minishell: syntax error near unexpected token `<'\n");
	else if((*lst)->next->type == APPEND)
		ft_printf("minishell: syntax error near unexpected token `>>'\n");
	else
		ft_printf("minishell: syntax error near unexpected token `|'\n");
	free_stackfinal(lst);
}

t_arg *ft_parser(t_arg *lst, t_shell *shell)

{
	t_arg	*final;
	t_arg	*node;
	t_arg	*nlast;
	int		i;
	int		j;
	int		k;
	int		l;
	t_arg	*head_arg;
	t_arg	*head_heredoc;
	t_arg	*head_output;
	t_arg	*head_input;

	int node_num = 0;//delete later
	final = NULL;
	if (!lst)
		return (NULL);
	while(lst)
	{
		head_arg = lst;
		head_heredoc = lst;
		head_output = lst;
		head_input = lst;
		node = ft_calloc(1, sizeof(t_arg));
		if (!node)
			return (NULL);
		i = 0;
		j = 0;
		k = 0;
		l = 0;

		while(lst)
		{
			if(lst->type == HEREDOC)
			{
				if(lst->next == NULL)
				{
					lst = lst->next;
					break;
				}
				if(lst->next->type == HEREDOC || lst->next->type == INPUT || lst->next->type == OUTPUT || lst->next->type == APPEND || lst->next->type == PIPE)//STDERROR
				{
					ft_printsyntaxerror(&lst);
					return(NULL);
				}
				node->in_file = ft_strdup("here_doc");
				lst = lst->next;
				i++;
				lst->type = GOING_HEREDOC;
			}
			else if(lst->type == ARG)
			{
				j++;
				lst->type = GOING_ARG;
			}
			else if(lst->type == OUTPUT)
			{
				if(lst->next == NULL)
				{
					lst = lst->next;
					break;
				}
				if(lst->next->type == HEREDOC || lst->next->type == INPUT || lst->next->type == OUTPUT || lst->next->type == APPEND || lst->next->type == PIPE)//STDERROR
				{
					ft_printsyntaxerror(&lst);
					return(NULL);
				}
				lst = lst->next;
				k++;
				lst->type = GOING_OUTPUT;
			}
			else if(lst->type == INPUT)
			{
				if(lst->next == NULL)
				{
					lst = lst->next;
					break;
				}
				if(lst->next->type == HEREDOC || lst->next->type == INPUT || lst->next->type == OUTPUT || lst->next->type == APPEND || lst->next->type == PIPE)//STDERROR
				{
					ft_printsyntaxerror(&lst);
					return(NULL);
				}
				lst = lst->next;
				l++;
				lst->type = GOING_INPUT;
			}
			else if(lst->type == APPEND)
			{
				if(lst->next == NULL)
				{
					lst = lst->next;
					break;
				}
				if(lst->next->type == HEREDOC || lst->next->type == INPUT || lst->next->type == OUTPUT || lst->next->type == APPEND || lst->next->type == PIPE)//STDERROR
				{
					ft_printsyntaxerror(&lst);
					return(NULL);
				}
				node->append = true;
				lst = lst->next;
				k++;
				lst->type = GOING_OUTPUT;
			}
			else if(lst->type == DOLLAR_SIGN)
			{
				j++;
				lst->type = GOING_DOLLAR_SIGN;
			}
			else if(lst->type == SINGLEQUOTE_DOLLAR)
			{	
				j++;
				lst->type = GOING_SINGLEQUOTE_DOLLAR;
			}
			else if(lst->type == DOUBLE_PIPE)
			{
				ft_printsyntaxerror(&lst);
				return(NULL);
			}
			else if(lst->type == PIPE)
			{
				if(lst->next == NULL)
				{
					lst = lst->next;
					break;
				}
				if(lst->next->type == HEREDOC || lst->next->type == INPUT || lst->next->type == OUTPUT || lst->next->type == APPEND || lst->next->type == PIPE)//STDERROR
				{
					ft_printsyntaxerror(&lst);
					return(NULL);
				}
				lst = lst->next;
				break;
			}
			lst = lst->next;
		}
		node_num++;
		printf("---NODE%i---\n", node_num);
		if(i != 0)
			node->here_doc = ft_strjoinline_heredoc(head_heredoc, i);
		if(j != 0)
			node->arguments = ft_strjoinline_args(head_arg, j, shell);
		if(k != 0)
			node->out_file = ft_strjoinline_output(head_output, k);
		if(l != 0)
			node->in_file_open = ft_strjoinline_input(head_input, l);
		if (!(final))
		{
			final = node;
			node->prev = NULL;
		}
		else
		{
			nlast = ft_stacklast(final);
			nlast->next = node;
			node->prev = nlast;
		}
	}
	node_num = 0;
 	t_arg *current = final;
    while (current)
	{
		node_num++;
		printf("---NODE%i---\n", node_num);
        printf("%sINPUT\n", current->in_file);
        printf("%iAPPEND\n", current->append);
        current = current->next;
    }
	return(final);
}
