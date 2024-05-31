/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:05:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/05/31 16:18:15 by thuy-ngu         ###   ########.fr       */
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
	while (str[i] == ' ')
	{
		i++;
		j++;
	}
	if (nospace == i)
		return (0);
	return (j);
}

int	shellcommand_scan(t_arg **lst, char *str, int i, t_sign **quote)
{
	int			j;
	int			h;
	int			type;
	t_append	info;

	j = 0;
	if (str[i] == '\0')
		return (j);
	if (str[i] == '>' && str[i + 1] != '>')
	{
		j = 1;
		type = OUTPUT;
	}
	else if (str[i] == '<' && str[i + 1] != '<')
	{
		j = 1;
		type = INPUT;
	}
	else if (str[i] == '|' && str[i + 1] != '|')
	{
		j = 1;
		type = PIPE;
	}
	else if (str[i] == '|' && str[i + 1] == '|')
	{
		j = 2;
		type = DOUBLE_PIPE;
	}
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		j = 2;
		type = HEREDOC;
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		j = 2;
		type = APPEND;
	}
	else if (str[i] == '$')
	{
		h = i;
		if ((*quote)->quote_type == FIRST_SINGLE_QUOTE)
			type = SINGLEQUOTE_DOLLAR;
		while (str[h] != ' ' && str[h])
		{
			if (find_quote(quote, str, h))
				break ;
			h++;
			j++;
		}
		if (type != SINGLEQUOTE_DOLLAR)
			type = DOLLAR_SIGN;
	}
	if (j > 0)
	{
		info.start = i;
		info.len = j;
		append_node(lst, str, info, type);
		return (j);
	}
	else
		return (0);
}

int	arg_scan(t_arg **lst, char *str, int i, t_sign **quote)
{
	int			j;
	int			type;
	int			start;
	t_append	info;

	start = i;
	j = 0;
	type = ARG;
	if (str[i] == '\0')
		return (j);
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		return (shellcommand_scan(lst, str, i, quote));
	while (str[i])
	{
		if ((*quote)->quote_type == 0)
		{
			if (skip_space(str, i))
				break ;
		}
		if ((*quote)->quote_type == 0)
		{
			if (str[i] == '|' || str[i] == '<' || str[i] == '>')
				break ;
		}
		if (find_quote(quote, str, i) == 1)
			break ;
		i++;
		j++;
	}
	info.start = start;
	info.len = j;
	if (j > 0)
		append_node(lst, str, info, type);
	return (j);
}

t_arg	*ft_lexer(char *str, t_arg *lst)
{
	int		i;
	t_arg	*head;
	t_sign	*quote;

	i = 0;
	if (!str || !*str)
		return (NULL);
	quote = ft_calloc(1, sizeof(t_sign));
	while (str[i])
	{
		i += skip_space(str, i);
		i += handle_quotestring(&lst, &quote, str, i);
		i += shellcommand_scan(&lst, str, i, &quote);
		if (quote->quote_type == 0)
			i += skip_space(str, i);
		i += arg_scan(&lst, str, i, &quote);
	}
	head = lst;
	if (quote->quote_type == FIRST_SINGLE_QUOTE || \
	quote->quote_type == FIRST_DOUBLE_QUOTE)
	{
		free(head);
		ft_printf("bash: syntax error: UNCLOSED_QUOTE\n");//return(EXIT_FAILURE) maybe shell->exit_status
		return (NULL);
	}
	return (lst);
}
