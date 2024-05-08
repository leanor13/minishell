/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/08 19:43:11 by yioffe           ###   ########.fr       */
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

// char	*ft_strjoinline(char *s1, char *s2)
// {
// 	char	*s3;
// 	size_t	i;
// 	size_t	j;

// 	s3 = (char *)malloc(sizeof(char) * (ft_strjoinlen(s1) + ft_strjoinlen(s2) + 2));
// 	if (!s3)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1 && s1[i])
// 		s3[j++] = s1[i++];
// 	i = 0;
// 	while (s2[i])
// 	{
// 		s3[j++] = s2[i];
// 		i++;
// 	}
// 	s3[j++] = ' ';
// 	s3[j] = '\0';
// 	free(s1);
// 	return (s3);
// }

char	*ft_strjoinline(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	s3 = (char *)malloc(sizeof(char) * (ft_strjoinlen(s1) + ft_strjoinlen(s2) + 3));
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

// static void	free_res(char **result, int i)
// {
// 	while (i > 0)
// 		free(result[--i]);
// 	free(result);
// }

static char	*put_word(char *s)
{
	char	*word;
	int		len;

	len = 0;
	// if (is_quote(s[len]))
	// {
	// 	q = *s;
	// 	s++;
	// 	while (s[len] && s[len] != q)
	// 		len++;
	// }
	// else
	while (s[len])
		len++;
		// while (s[len] && (s[len] != c))
		// 	len++;
	word = ft_substr(s, 0, len);
	if (!word)
	{
		perror("Failed split word memory allocation");
		return (NULL);
	}
	return (word);
}

void print_string(const char *str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

char	**ft_strjoinline_splitversion(t_arg *lst, int i)
{
	size_t	j;
	size_t	k;
	char **s1;

	j = 0;
	k = 0;
	s1 = (char **)malloc((i + 1) * sizeof(char *));
	if (!s1)
		return (NULL);
	int count = 0;
	while (count < i)
	{
		if(lst->type == ARG)
		{
			s1[count] = put_word(lst->str);
			//printf("BELEP\n");
			printf("Content of s1[%d]: ", count);
            print_string(s1[count]);
			count++;
		}
		// if (!s1[count])// MAYBE SOME OTHER PROTECTION THIS ONE IS NOT WORKING
		// 	return (free_res(s1, count), NULL);
		lst = lst->next;
	}
	// while (lst)
	// {
	// 	if(lst->type == ARG)
	// 	{
	// 		s1[count] = put_word(lst->str);
	// 		printf("BELEP\n");
	// 		printf("Content of s1[%d\n]: ", count);
    //         print_string(s1[count]);
	// 		count++;
	// 	}
	// 	// if (!s1[count])// MAYBE SOME OTHER PROTECTION THIS ONE IS NOT WORKING
	// 	// 	return (free_res(s1, count), NULL);
	// 	lst = lst->next;
	// }
	// while (lst)//maybe just s2[i]
	// {
	// 	if(lst->type == ARG)
	// 	{
	// 		arg_str = ft_strdup(lst->str);
	// 		k = 0;
	// 		j = 0;
	// 		while(arg_str[k])
	// 		{
	// 			s1[l][j++] = arg_str[k++];
	// 			printf("%cMOST\n", s1[l][j]);
	// 		}
	// 		free(arg_str);
	// 		l++;
	// 	}
	// 	lst = lst->next;
	// }
	s1[count] = NULL;
	// char **arg_str;
 	// t_arg *current = final;
	// arg_str = current->args_doublechar;
	// int y = 0;
	// int x = 0;
	// while (arg_str[y] != NULL)
	// {
	// 	x = 0;
	// 	 while (arg_str[y][x] != '\0')
	// 	{
	// 		printf("%c\n", arg_str[y][x]);
	// 		x++;
	// 	}
	// 	y++;
	// }
	return(s1);
}


// char	*ft_strcutspace(char *s1)
// {
// 	char	*s2;
// 	size_t	j;
// 	size_t	i;
// 	int	len;

// 	len = ft_strlen(s1);
// 	s2 = (char *)malloc(sizeof(char) * (len));
// 	if (!s2)
// 		return (NULL);
// 	j = 0;
// 	i = 0;
// 	while (s1 && s1[i] && (len - 1) > j)
// 		s2[j++] = s1[i++];
// 	s2[j] = '\0';
// 	free(s1);
// 	return (s2);
// }

t_arg *ft_parser(t_arg *lst)
{
	t_arg	*final;
	t_arg	*node;
	t_arg	*nlast;
	int		i;
	t_arg	*head;

	i = 0;
	final = NULL;
	if (!lst)
		return (NULL);
	head = lst;
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
			// else if(lst->type == ARG)
			//  	node->args = ft_strjoinline(node->args, lst->str);
			else if(lst->type == ARG)
				i++;
			else if(lst->type == OUTPUT)
			{
				lst = lst->next;
				node->out_file = ft_strdup(lst->str); //+ ' '
			}
			else if(lst->type == INPUT)
			{
				printf("input enter\n");
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
		node->args_doublechar = ft_strjoinline_splitversion(head, i);
		//node->args = ft_strcutspace(node->args);
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
        printf("%iAPPEND\n", current->append);
        current = current->next;
    }
	return(final);
}
