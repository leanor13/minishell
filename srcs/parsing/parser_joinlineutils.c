/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_joinlineutils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/10 18:08:02 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*put_word(char *s)
{
	int		len;
	char	*word;

	len = 0;
	if (!s)
		return (NULL);
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

char	**ft_strjoinline_heredoc(t_arg *lst, int i)
{
	char	**s1;
	int		count;

	count = 0;
	s1 = (char **)malloc((i + 1) * sizeof(char *));
	if (!s1)
		return (NULL);
	while (lst && count < i)
	{
		if (lst->type == GOING_HEREDOC)
		{
			s1[count] = put_word(lst->str);
			//printf("Content of heredoc s1[%d]: ", count);//DELETE
			//print_string(s1[count]);//DELETE
			count++;
		}
		lst = lst->next;
	}
	s1[count] = NULL;
	return (s1);
}

char	**ft_strjoinline_output(t_arg *lst, int i)
{
	char	**s1;
	int		count;

	count = 0;
	s1 = (char **)malloc((i + 1) * sizeof(char *));
	if (!s1)
		return (NULL);
	while (lst && count < i)
	{
		if (lst->type == GOING_OUTPUT)
		{
			s1[count] = put_word(lst->str);
			//printf("Content of output s1[%d]: ", count);//DELETE
			//print_string(s1[count]);//DELETE
			count++;
		}
		lst = lst->next;
	}
	s1[count] = NULL;
	return (s1);
}

char	**ft_strjoinline_input(t_arg *lst, int i)
{
	char	**s1;
	int		count;

	count = 0;
	s1 = (char **)malloc((i + 1) * sizeof(char *));
	if (!s1)
		return (NULL);
	while (lst && count < i)
	{
		if (lst->type == GOING_INPUT)
		{
			s1[count] = put_word(lst->str);
			//printf("Content of input s1[%d]: ", count);//DELETE
			//print_string(s1[count]);//DELETE
			count++;
		}
		lst = lst->next;
	}
	s1[count] = NULL;
	return (s1);
}
