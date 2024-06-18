/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 17:10:08 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_single_character(char *str, int i, int *type)
{
	if (str[i] == '>' && str[i + 1] != '>')
	{
		*type = OUTPUT;
		return (1);
	}
	else if (str[i] == '<' && str[i + 1] != '<')
	{
		*type = INPUT;
		return (1);
	}
	else if (str[i] == '|' && str[i + 1] != '|')
	{
		*type = PIPE;
		return (1);
	}
	return (0);
}

int	handle_double_character(char *str, int i, int *type)
{
	if (str[i] == '|' && str[i + 1] == '|')
	{
		*type = DOUBLE_PIPE;
		return (2);
	}
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		*type = HEREDOC;
		return (2);
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		*type = APPEND;
		return (2);
	}
	return (0);
}

static int	handle_dollar_sign(char *str, int i, t_sign **quote, int *type)
{
	int	j;
	int	h;

	j = 0;
	h = i;
	if ((*quote)->quote_type == FIRST_SINGLE_QUOTE)
		*type = SINGLEQUOTE_DOLLAR;
	while (str[h] != ' ' && str[h])
	{
		if (find_quote(quote, str, h))
			break ;
		h++;
		j++;
	}
	if (*type != SINGLEQUOTE_DOLLAR)
		*type = DOLLAR_SIGN;
	return (j);
}

int	shellcommand_scan(t_arg **lst, char *str, int i, t_sign **quote)
{
	int			j;
	int			type;
	t_append	info;

	j = 0;
	type = NONE_TYPE;
	if (str[i] == '\0')
		return (j);
	j = handle_single_character(str, i, &type);
	if (j == 0)
		j = handle_double_character(str, i, &type);
	if (j == 0 && str[i] == '$')
		j = handle_dollar_sign(str, i, quote, &type);
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
