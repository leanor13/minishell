/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_joinlineutils_args.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 14:16:05 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int

static int	handle_dollar_sign(t_arg *lst, t_shell *shell, char **s1, int count)
{
	int		i;
	t_env	*list;
	char	*var_value;

	i = 0;
	i = 
	if (lst->str[1] == '?')
	{
		var_value = ft_itoa(shell->exit_status);
		i = 1;
	}
	else
	{
		list = env_find_var(shell->env_list, &lst->str[1]);
		if (list)
			var_value = list->var_value;
		if (!list)
			return (count);
	}
	if (var_value && var_value[0])
	{
		s1[count] = put_word(var_value);
		count++;
	}
	if (i == 1)
		free (var_value);
	return (count);
}

static int	handle_arg(t_arg *lst, char **s1, int count)
{
	if (lst->type == GOING_ARG || lst->type == GOING_SINGLEQUOTE_DOLLAR)
		s1[count++] = put_word(lst->str);
	return (count);
}

char	**ft_strjoin_args(t_arg *lst, int i, t_shell *shell)
{
	char	**s1;
	int		count;

	s1 = (char **)malloc((i + 1) * sizeof(char *));
	if (!s1)
		return (NULL);
	count = 0;
	while (lst && count < i)
	{
		if (lst->type == GOING_ARG || lst->type == GOING_SINGLEQUOTE_DOLLAR)
			count = handle_arg(lst, s1, count);
		if (lst->type == GOING_DOLLAR_SIGN)
			count = handle_dollar_sign(lst, shell, s1, count);
		lst = lst->next;
	}
	s1[count] = NULL;
	return (s1);
}
