/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_joinlineutils_args.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/02 14:27:27 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_string(const char *str)// DELETE
{
	for (size_t i = 0; str[i] != '\0'; i++) 
	{
		printf("%c", str[i]);
	}
	printf("\n");
}

static char	*put_word(char *s)
{
	char	*word;
	int		len;

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

char	**ft_strjoinline_args(t_arg *lst, int i, t_shell *shell)
{
	char	**s1;
	char	*var_value;
	int		count;
	char	*res;
	t_env	*list;

	s1 = (char **)malloc((i + 1) * sizeof(char *));
	if (!s1)
		return (NULL);
	count = 0;
	while (lst && count < i)
	{
		if (lst->type == GOING_ARG || lst->type == GOING_SINGLEQUOTE_DOLLAR)
			s1[count] = put_word(lst->str);
		if (lst->type == GOING_DOLLAR_SIGN)
		{
			if (lst->str[1] == '?')
			{
				res = ft_itoa(shell->exit_status);
				ft_strcat(res, &lst->str[2]);
				var_value = ft_strdup(res);
			}
			else
			{
				list = env_find_var(shell->env_list, &lst->str[1]);
				if (list)
					var_value = list->var_value;
				if (!list)
					break ;
			}
			if (var_value && var_value[0])
				s1[count] = put_word(var_value);
		}
		//printf("Content of args s1[%d]: ", count);//DELETE
		//print_string(s1[count]);//DELETE
		count++;
		lst = lst->next;
	}
	s1[count] = NULL;
	return (s1);
}
