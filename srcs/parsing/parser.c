/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 14:22:30 by thuy-ngu         ###   ########.fr       */
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

void	more_parsing(t_arg **lst, t_arg **node, t_arg **temp_lst, t_heads *heads)
{
	while (*lst)
	{
		if (if_heredoc(lst,node, temp_lst, heads))
			return ;
		if (if_arg(lst,node, temp_lst, heads))
			return ;
		if ((*lst)->type == OUTPUT)
		{
			if ((*lst)->next == NULL)
			{
				*lst = (*lst)->next;
				break;
			}
			if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT || \
			(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND \
			|| (*lst)->next->type == PIPE)
			{
				ft_printsyntaxerror(lst);
				free_args(node);
				free_args(temp_lst);
				return ;
			}
			*lst = (*lst)->next;
			heads->k++;
			(*lst)->type = GOING_OUTPUT;
		}
		else if ((*lst)->type == INPUT)
		{
			if ((*lst)->next == NULL)
			{
				*lst = (*lst)->next;
				break;
			}
			if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT || \
			(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND \
			|| (*lst)->next->type == PIPE)
			{
				ft_printsyntaxerror(lst);
				free_args(node);
				free_args(temp_lst);
				return ;
			}
			*lst = (*lst)->next;
			heads->l++;
			(*lst)->type = GOING_INPUT;
		}
		else if ((*lst)->type == APPEND)
		{
			if ((*lst)->next == NULL)
			{
				*lst = (*lst)->next;
				break;
			}
			if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT || \
			(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND \
			|| (*lst)->next->type == PIPE)
			{
				ft_printsyntaxerror(lst);
				free_args(node);
				free_args(temp_lst);
				return ;
			}
			(*node)->append = true;
			*lst = (*lst)->next;
			heads->k++;
			(*lst)->type = GOING_OUTPUT;
		}
		else if ((*lst)->type == DOLLAR_SIGN)
		{
			heads->j++;
			(*lst)->type = GOING_DOLLAR_SIGN;
		}
		else if ((*lst)->type == SINGLEQUOTE_DOLLAR)
		{
			heads->j++;
			(*lst)->type = GOING_SINGLEQUOTE_DOLLAR;
		}
		else if ((*lst)->type == DOUBLE_PIPE)
		{
			ft_printsyntaxerror(lst);
			free_args(node);
			free_args(temp_lst);
			return ;
		}
		else if ((*lst)->type == PIPE)
		{
			if ((*lst)->next == NULL)
			{
				*lst = (*lst)->next;
				break;
			}
			if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT || \
			(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND \
			|| (*lst)->next->type == PIPE)
			{
				ft_printsyntaxerror(lst);
				free_args(node);
				free_args(temp_lst);
				return ;
			}
			*lst = (*lst)->next;
			break;
		}
		*lst = (*lst)->next;
	}
}

t_arg	*ft_parser(t_arg *lst, t_shell *shell)
{
	t_arg	*final;
	t_arg	*node;
	t_arg	*nlast;
	t_arg	*temp_lst;
	t_heads	heads;

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
		if(!temp_lst)
			return(NULL);
		if (heads.i != 0)
			node->here_doc = ft_strjoin_heredoc(heads.head_heredoc, heads.i);
		if (heads.j != 0)
			node->arguments = ft_strjoin_args(heads.head_arg, heads.j, shell);
		if (heads.k != 0)
			node->out_file = ft_strjoin_output(heads.head_output, heads.k);
		if (heads.l != 0)
			node->in_file = ft_strjoin_input(heads.head_input, heads.l);
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
	free_args(&temp_lst);
	return (final);
}
t_arg	*ft_parser(t_arg *lst, t_shell *shell)
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
	t_arg	*temp_lst = lst;

	//int node_num = 0;//DELETE
	final = NULL;
	if (!lst)
		return (NULL);
	while(lst)
	{
		head_arg = lst;
		head_heredoc = lst;
		head_output = lst;
		head_input = lst;
		//node = lst;
		node = ft_calloc(1, sizeof(t_arg));
		if (!node)
		{
			free_args(&temp_lst);
			return (NULL);
		}
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
					free_args(&final);
					free_args(&temp_lst);
					return(NULL);
				}
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
					free_args(&final);
					free_args(&temp_lst);
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
					free_args(&final);
					free_args(&temp_lst);
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
					free_args(&final);
					free_args(&temp_lst);
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
				free_args(&final);
				free_args(&temp_lst);
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
					free_args(&final);
					free_args(&temp_lst);
					return(NULL);
				}
				lst = lst->next;
				break;
			}
			lst = lst->next;
		}
		//node_num++;//DELETE
		//printf("---NODE%i---\n", node_num);//DELETE
		if(i != 0)
			node->here_doc = ft_strjoinline_heredoc(head_heredoc, i);
		if(j != 0)
			node->arguments = ft_strjoinline_args(head_arg, j, shell);
		if(k != 0)
			node->out_file = ft_strjoinline_output(head_output, k);
		if(l != 0)
			node->in_file = ft_strjoinline_input(head_input, l);
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

	/* node_num = 0;//DELETE
 	t_arg *current = final;//DELETE
    while (current)//DELETE
	{
		node_num++;
		printf("---NODE%i---\n", node_num);
        printf("%iAPPEND\n", current->append);
        current = current->next;
    }//DELETE */
	free_args(&temp_lst);
	return(final);
}
