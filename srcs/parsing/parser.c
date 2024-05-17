/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/17 21:53:54 by thuy-ngu         ###   ########.fr       */
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

static char	*put_word(char *s)
{
	char	*word;
	int		len;

	len = 0;
	while (s[len])
		len++;
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

char	**ft_strjoinline_args(t_arg *lst, int i)
{
	char **s1;

	s1 = (char **)malloc((i + 1) * sizeof(char *));
	if (!s1)
		return (NULL);
	int count = 0;
	while (lst && count < i)
	{
		if(lst->type == GOING_ARG)
		{
			s1[count] = put_word(lst->str);
			//printf("ENTER STRJOINLINE ARGS\n");
			printf("Content of args s1[%d]: ", count);
            print_string(s1[count]);
			count++;
		}
		// if (!s1[count])// MAYBE SOME OTHER PROTECTION THIS ONE IS NOT WORKING
		// 	return (free_res(s1, count), NULL);
		lst = lst->next;
	}
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

char	**ft_strjoinline_heredoc(t_arg *lst, int i)
{
	char **s1;

	s1 = (char **)malloc((i + 1) * sizeof(char *));
	if (!s1)
		return (NULL);
	int count = 0;
	while (lst && count < i)
	{
		if(lst->type == GOING_HEREDOC)
		{
			s1[count] = put_word(lst->str);
			//printf("ENTER STRJOINLINE ARGS\n");
			printf("Content of heredoc s1[%d]: ", count);
			print_string(s1[count]);
			count++;
		}
		// if (!s1[count])// MAYBE SOME OTHER PROTECTION THIS ONE IS NOT WORKING
		// 	return (free_res(s1, count), NULL);
		lst = lst->next;
	}
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

char	**ft_strjoinline_output(t_arg *lst, int i)
{
	char **s1;

	s1 = (char **)malloc((i + 1) * sizeof(char *));
	if (!s1)
		return (NULL);
	int count = 0;
	while (lst && count < i)
	{
		if(lst->type == GOING_OUTPUT)
		{
			s1[count] = put_word(lst->str);
			//printf("ENTER STRJOINLINE ARGS\n");
			printf("Content of output s1[%d]: ", count);
            print_string(s1[count]);
			count++;
		}
		// if (!s1[count])// MAYBE SOME OTHER PROTECTION THIS ONE IS NOT WORKING
		// 	return (free_res(s1, count), NULL);
		lst = lst->next;
	}
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

char	**ft_strjoinline_input(t_arg *lst, int i)
{
	char **s1;

	s1 = (char **)malloc((i + 1) * sizeof(char *));
	if (!s1)
		return (NULL);
	int count = 0;
	while (lst && count < i)
	{
		if(lst->type == GOING_INPUT)
		{
			s1[count] = put_word(lst->str);
			//printf("ENTER STRJOINLINE ARGS\n");
			printf("Content of input s1[%d]: ", count);
            print_string(s1[count]);
			count++;
		}
		// if (!s1[count])// MAYBE SOME OTHER PROTECTION THIS ONE IS NOT WORKING
		// 	return (free_res(s1, count), NULL);
		lst = lst->next;
	}
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

void	ft_printsyntaxerror(t_arg **lst)
{
	if((*lst)->next->type == HEREDOC)
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
	//	free(command);
}

t_arg *ft_parser(t_arg *lst)
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
		printf("okay\n");
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
			else if(lst->type == PIPE)
			{
				printf("okay\n");
				if(lst->next == NULL)
				{
					lst = lst->next;
					return(NULL);
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
			node->arguments = ft_strjoinline_args(head_arg, j);
		if(k != 0)
			node->out_file = ft_strjoinline_output(head_output, k);
		if(l != 0)
			node->in_file_open = ft_strjoinline_input(head_input, l);
		//MAYBE CHANGE HEREDOC
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
		// printf("%sOUTPUT\n", current->out_file);
		// printf("%sHEREDOC\n", current->here_doc);
		node_num++;
		printf("---NODE%i---\n", node_num);
        printf("%sINPUT\n", current->in_file);
        printf("%iAPPEND\n", current->append);
        current = current->next;
    }
	return(final);
}
