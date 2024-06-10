/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/10 15:48:09 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_printsyntaxerror(t_arg **lst) //TAKE CARE OF EXIT STATUS
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
	free_args(lst);
}

// static int	handle_heredoc(t_arg **lst, t_arg **temp_lst)
// {
// 	if ((*lst)->next == NULL)
// 	{
// 		*lst = (*lst)->next;
// 		return (1);
// 	}
// 	if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT ||
// 		(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND ||
// 		(*lst)->next->type == PIPE)
// 	{
// 		free_args(temp_lst);
// 		ft_printsyntaxerror(lst);
// 		return (1);
// 	}
// 	*lst = (*lst)->next;
// 	(*lst)->type = GOING_HEREDOC;
// 	return (0);
// }

// static int	handle_output(t_arg **lst, t_arg **temp_lst, t_arg *node)
// {
// 	if ((*lst)->next == NULL)
// 	{
// 		*lst = (*lst)->next;
// 		return (1);
// 	}
// 	if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT ||
// 		(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND ||
// 		(*lst)->next->type == PIPE)
// 	{
// 		free_args(temp_lst);
// 		ft_printsyntaxerror(lst);
// 		return (1);
// 	}
// 	if ((*lst)->type == APPEND)
// 		node->append = true;
// 	*lst = (*lst)->next;
// 	(*lst)->type = GOING_OUTPUT;
// 	return (0);
// }

// static int	handle_input(t_arg **lst, t_arg **temp_lst)
// {
// 	if ((*lst)->next == NULL)
// 	{
// 		*lst = (*lst)->next;
// 		return (1);
// 	}
// 	if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT ||
// 		(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND ||
// 		(*lst)->next->type == PIPE)
// 	{
// 		free_args(temp_lst);
// 		ft_printsyntaxerror(lst);
// 		return (1);
// 	}
// 	*lst = (*lst)->next;
// 	(*lst)->type = GOING_INPUT;
// 	return (0);
// }

// static int	handle_pipe(t_arg **lst, t_arg **temp_lst)
// {
// 	if ((*lst)->next == NULL)
// 	{
// 		*lst = (*lst)->next;
// 		return (1);
// 	}
// 	if ((*lst)->next->type == HEREDOC || (*lst)->next->type == INPUT ||
// 		(*lst)->next->type == OUTPUT || (*lst)->next->type == APPEND ||
// 		(*lst)->next->type == PIPE)
// 	{
// 		free_args(temp_lst);
// 		ft_printsyntaxerror(lst);
// 		return (1);
// 	}
// 	*lst = (*lst)->next;
// 	return (0);
// }

// static int	handle_dollar(t_arg **lst)
// {
// 	(*lst)->type = GOING_DOLLAR_SIGN;
// 	return (0);
// }

// static int	handle_singlequote_dollar(t_arg **lst)
// {
// 	(*lst)->type = GOING_SINGLEQUOTE_DOLLAR;
// 	return (0);
// }

// static void	set_node_types(t_arg *node, t_arg **lst, int *counts, t_shell *shell)
// {
// 	if (counts[0] != 0)
// 		node->here_doc = ft_strjoinline_heredoc(*lst, counts[0]);
// 	if (counts[1] != 0)
// 		node->arguments = ft_strjoinline_args(*lst, counts[1], shell);
// 	if (counts[2] != 0)
// 		node->out_file = ft_strjoinline_output(*lst, counts[2]);
// 	if (counts[3] != 0)
// 		node->in_file = ft_strjoinline_input(*lst, counts[3]);
// }

// static int	handle_arg(t_arg **lst)
// {
// 	(*lst)->type = GOING_ARG;
// 	return (0);
// }

// static void	init_counts(int *counts)
// {
// 	counts[0] = 0; // i
// 	counts[1] = 0; // j
// 	counts[2] = 0; // k
// 	counts[3] = 0; // l
// }

// static t_arg	*create_node(t_arg **temp_lst)
// {
// 	t_arg	*node;

// 	node = ft_calloc(1, sizeof(t_arg));
// 	if (!node)
// 	{
// 		free_args(temp_lst);
// 		return (NULL);
// 	}
// 	return (node);
// }

// static void	add_node_to_final(t_arg **final, t_arg *node)
// {
// 	t_arg	*nlast;

// 	if (!(*final))
// 	{
// 		*final = node;
// 		node->prev = NULL;
// 	}
// 	else
// 	{
// 		nlast = ft_stacklast(*final);
// 		nlast->next = node;
// 		node->prev = nlast;
// 	}
// }

// static void	update_counts(int type, int *counts)
// {
// 	if (type == HEREDOC)
// 		counts[0]++;
// 	else if (type == ARG)
// 		counts[1]++;
// 	else if (type == OUTPUT)
// 		counts[2]++;
// 	else if (type == INPUT)
// 		counts[3]++;
// }

// t_arg	*ft_parser(t_arg *lst, t_shell *shell)
// {
// 	t_arg	*final;
// 	t_arg	*node;
// 	t_arg	*temp_lst;
// 	int		counts[4];

// 	final = NULL;
// 	if (!lst)
// 		return (NULL);
// 	temp_lst = lst;
// 	while (lst)
// 	{
// 		node = create_node(&temp_lst);
// 		if (!node)
// 			return (NULL);
// 		init_counts(counts);
// 		while (lst)
// 		{
// 			if (lst->type == HEREDOC && handle_heredoc(&lst, &temp_lst))
// 				break;
// 			else if (lst->type == ARG && handle_arg(&lst))
// 				break;
// 			else if ((lst->type == OUTPUT || lst->type == APPEND) &&
// 				handle_output(&lst, &temp_lst, node))
// 				break;
// 			else if (lst->type == INPUT && handle_input(&lst, &temp_lst))
// 				break;
// 			else if (lst->type == DOLLAR_SIGN && handle_dollar(&lst))
// 				break;
// 			else if (lst->type == SINGLEQUOTE_DOLLAR && handle_singlequote_dollar(&lst))
// 				break;
// 			else if (lst->type == DOUBLE_PIPE)
// 			{
// 				free_args(&temp_lst);
// 				ft_printsyntaxerror(&lst);
// 				return (NULL);
// 			}
// 			else if (lst->type == PIPE && handle_pipe(&lst, &temp_lst))
// 				break;
// 			update_counts(lst->type, counts);
// 			lst = lst->next;
// 		}
// 		set_node_types(node, &lst, counts, shell);
// 		add_node_to_final(&final, node);
// 	}
// 	free_args(&temp_lst);
// 	return (final);
// }

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
					free_args(&temp_lst);
					ft_printsyntaxerror(&lst);
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
					free_args(&temp_lst);
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
					free_args(&temp_lst);
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
					free_args(&temp_lst);
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
				free_args(&temp_lst);
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
					free_args(&temp_lst);
					ft_printsyntaxerror(&lst);
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
	if(temp_lst)
		free_args(&temp_lst);
	return(final);
}
