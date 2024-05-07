/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/07 15:28:24 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*ft_strcutspace(char *s1)
{
	char	*s2;
	size_t	j;
	size_t	i;
	int	len;

	len = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (len));
	if (!s2)
		return (NULL);
	j = 0;
	i = 0;
	while (s1 && s1[i] && (len - 1) > (int) j)
		s2[j++] = s1[i++];
	s2[j] = '\0';
	free(s1);
	return (s2);
}

t_arg *ft_parser(t_arg *lst)
{
	t_arg	*final;
	t_arg	*node;
	t_arg	*nlast;

	final = NULL;
	if (!lst)
		return (NULL);
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
			 	node->args = ft_strjoinline(node->args, lst->str);
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
		node->args = ft_strcutspace(node->args);
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

