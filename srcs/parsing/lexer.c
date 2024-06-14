/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:05:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/06/14 17:42:24 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_space(char *str, int i)
{
	int	nospace;
	int	j;

	j = 0;
	if (str[i] == '\0')
		return (j);
	nospace = i;
	while (str[i] == ' ' || str[i] == '\t')
	{
		i++;
		j++;
	}
	if (nospace == i)
		return (0);
	return (j);
}

void	scan_string(char *str, t_arg **lst, t_sign **quote)
{
	int	i;
	int	k;

	i = 0;
	while (str[i])
	{
		i += skip_space(str, i);
		i += handle_quotestring(lst, quote, str, i);
		k = i;
		i += shellcommand_scan(lst, str, i, quote);
		if (i > k)
			i += handle_quotestring(lst, quote, str, i);
		if ((*quote)->quote_type == 0)
			i += skip_space(str, i);
		i += arg_scan(lst, str, i, quote);
	}
}

int	scan_argument(char *str, int *i, t_sign **quote, \
t_append *info)
{
	int	j;
	int	start;

	start = *i;
	j = 0;
	while (str[*i])
	{
		if ((*quote)->quote_type == 0)
		{
			if (skip_space(str, *i))
				break ;
		}
		if ((*quote)->quote_type == 0)
		{
			if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
				break ;
		}
		if (find_quote(quote, str, *i) == 1)
			break ;
		(*i)++;
		j++;
	}
	info->start = start;
	info->len = j;
	return (j);
}

int	arg_scan(t_arg **lst, char *str, int i, t_sign **quote)
{
	int			j;
	int			type;
	t_append	info;

	type = ARG;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		return (shellcommand_scan(lst, str, i, quote));
	j = scan_argument(str, &i, quote, &info);
	if (j > 0)
		append_node(lst, str, info, type);
	return (j);
}

t_arg	*ft_lexer(char *str, t_arg *lst)
{
	t_sign	*quote;

	if (!str || !*str)
		return (NULL);
	quote = ft_calloc(1, sizeof(t_sign));
	if (!quote)
	{
		perror("Memory allocation for lexer failed");
		return (NULL);
	}
	scan_string(str, &lst, &quote);
	if (quote->quote_type == FIRST_SINGLE_QUOTE || \
	quote->quote_type == FIRST_DOUBLE_QUOTE)
	{
		free(quote);
		free_args(&lst);
		ft_printf("bash: syntax error: unclosed quote\n");
		return (NULL);
	}
	free(quote);
	return (lst);
}
