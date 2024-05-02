/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/02 18:40:32 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	setup_struct(t_arg *arg)
// {
// 	arg->str = NULL;
// 	arg->type = 0;
// 	arg->args = NULL;
// 	arg->in_file = NULL;
// 	arg->out_file = NULL;
// 	arg->here_doc = NULL;
// 	arg->append = 0;
// 	arg->command = NULL;
// 	arg->path = NULL;
// 	arg->args_parsed = NULL;
// 	arg->built_in_fn = NULL;
// 	arg->next = NULL;
// 	arg->prev = NULL;
// }
// CHANGE THE PASSING VALUES

// void	find_heredoc(t_arg *lst)
// {
// 	lst->heredoc = 0;
// 	while(lst)
// 	{
// 		if(lst->type == HEREDOC)
// 		{
// 			lst->heredoc = 1;
// 			printf("ITTVAN");
// 		}
// 		if(lst->type == PIPE)
// 			break;
// 		lst = lst->next;
// 	}
// }

void	append_node_parser(t_arg **lst, char *str, int start, int len, int value)
{
	t_arg	*node;
	t_arg	*nlast;

	if (!lst)
		return ;
	node = malloc(sizeof(t_arg));
	if (!node)
		return ;
	node->next = NULL;
	node->str = ft_substr(str, start, len);
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

size_t	ft_strjoinlen(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);// THIS IS IMPORTANT protection here
	while (s[len] && s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoinline(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	s3 = (char *)malloc(sizeof(char) * (ft_strjoinlen(s1) + ft_strjoinlen(s2) + 2));
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		s3[j++] = s2[i];
		i++;
	}
	s3[j++] = ' ';
	s3[j] = '\0';
	free(s1);
	return (s3);
}

t_arg *ft_parser(t_arg *lst)
{
	t_arg	*final;
	t_arg	*node;
	t_arg	*nlast;

	final = NULL;
	if (!lst)
		return (NULL);// thinking on this protection how could you break sent nothing
	while(lst)
	{
		node = ft_calloc(1, sizeof(t_arg));
		if (!node)
			return (NULL);
		while(lst)
		{
			if(lst->type == HEREDOC)
			{
				lst = lst->next;
				node->here_doc = ft_strdup(lst->str);
			}
			// else if(lst->type == ARG)
			// 	node->args = ft_strdup(lst->str);
			else if(lst->type == ARG)
			{
				printf("lst->str, %s\n", lst->str);
				printf("node->args, %s\n", node->args);
			 	node->args = ft_strjoinline(node->args, lst->str);
			}
			else if(lst->type == OUTPUT)
			{
				lst = lst->next;
				node->out_file = ft_strdup(lst->str); //+ ' '
			}
			else if(lst->type == INPUT)
			{
				lst = lst->next;
				node->in_file = ft_strdup(lst->str);
			}
			else if(lst->type == APPEND)
			{
				node->append = true;
				lst = lst->next;
				node->out_file = ft_strdup(lst->str);
			}
			else if(lst->type == PIPE)
			{
				lst = lst->next;
				break;
			}
			lst = lst->next;
		}
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
 	t_arg *current = final;
    while (current)
    {
        printf("%sOUTPUT\n", current->out_file);
        printf("%sHEREDOC\n", current->here_doc);
        printf("%sINPUT\n", current->in_file);
        printf("%sARGS\n", current->args);
        printf("%iAPPEND\n", current->append);
        current = current->next;
    }
	return(final);
}

// t_arg *ft_parser(t_arg *lst)
// {
// 	t_arg **final;
// 	t_arg	*node;
// 	t_arg	*nlast;
// 	final = NULL;
// 	while(lst)
// 	{
// 		find_heredoc(lst);// node and final first connect the valuses, where you allocate the memory
// 		node = NULL;
// 		nlast = NULL;
// 		node->args = NULL;
// 		node = malloc(sizeof(t_arg));
// 		if (!node)
// 			return (NULL);
// 		while(lst)
// 		{
// 			if(lst->heredoc == 1)
// 				ft_strcpy(node->here_doc, lst->str);
// 			else if(lst->type == ARG)
// 				node->args = ft_strjoinline(node->args, lst->str);
// 			else if(lst->type == OUTPUT)
// 			{
// 				lst = lst->next;
// 				ft_strcpy(node->out_file, lst->str);
// 			}
// 			else if(lst->type == OUTPUT)
// 			{
// 				lst = lst->next;
// 				ft_strcpy(node->in_file, lst->str);
// 			}
// 			else if(lst->type == APPEND)
// 				node->append = true;
// 			else if(lst->type == PIPE)
// 				break;
// 			lst = lst->next;
// 		}
// 		if (!(*final))
// 		{
// 			*final = node;
// 			node->prev = NULL;
// 		}
// 		else
// 		{
// 			nlast = ft_stacklast(*final);
// 			nlast->next = node;
// 			node->prev = nlast;
// 		}
// 		free_stackfinal(&node);
// 		free_stackfinal(&nlast);
// 	}
// 	//free_stackfinal(&lst);
// 	//if delone, del the >, <, >>, << split, if pipe
// 	return(*final);
// }

// t_arg *ft_parser(t_arg *lst)
// {
// 	t_arg *final;
// 	// final->args = NULL;
// 	// final->out_file = NULL;
// 	// final->in_file = NULL;
// 	// final->here_doc = NULL;
// 	// final->append = 0;
	
// 	final = NULL;
// 		find_heredoc(lst);
// 	while(lst)
// 	{
// 		if(lst->heredoc == 1)
// 			ft_strcpy(final->here_doc, lst->str);
// 		else if(lst->type == ARG)
// 			final->args = ft_strjoinline(final->args, lst->str);
// 		else if(lst->type == OUTPUT)
// 		{
// 			lst = lst->next;
// 			ft_strcpy(lst->out_file, lst->str);
// 		}
// 		else if(lst->type == OUTPUT)
// 		{
// 			lst = lst->next;
// 			ft_strcpy(lst->in_file, lst->str);
// 		}
// 		else if(lst->type == APPEND)
// 			lst->append = true;
// 		else if(lst->type == PIPE)
// 		{
// 			append_node_parser
// 		}
// 		lst = lst->next;
// 	}
// 	free_stackfinal(&lst);
// 	//if delone, del the >, <, >>, << split, if pipe
// 	return(final);
// }