/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 16:39:47 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_second_single(t_arg **lst, t_sign **quote, char *str, int i)
{
	t_append	info;

	if ((*quote)->quote_type == FIRST_SINGLE_QUOTE)
	{
		if ((str[i] == 39 && str[i + 1] == 39))
		{
			ft_bzero(*quote, 1);
			info.start = 0;
			info.len = 0;
			append_node(lst, "\0", info, ARG);
			return (2);
		}
		else
			return (1);
	}
	return (0);
}

int	find_second_double(t_arg **lst, t_sign **quote, char *str, int i)
{
	t_append	info;

	if ((*quote)->quote_type == FIRST_DOUBLE_QUOTE)
	{
		if ((str[i] == 34 && str[i + 1] == 34))
		{
			ft_bzero(*quote, 1);
			info.start = 0;
			info.len = 0;
			append_node(lst, "\0", info, ARG);
			return (2);
		}
		else
			return (1);
	}
	return (0);
}

int	double_or_first(t_sign **quote, char *str, int i)
{
	if ((str[i] == 34 && str[i + 1] == 34) || \
	(str[i] == 39 && str[i + 1] == 39))
	{
		(*quote)->quote_type = 0;
		return (2);
	}
	if (str[i] == 34)
	{
		(*quote)->quote_type = FIRST_DOUBLE_QUOTE;
		return (1);
	}
	if (str[i] == 39)
	{
		(*quote)->quote_type = FIRST_SINGLE_QUOTE;
		return (1);
	}
	return (0);
}

int	handle_quotestring(t_arg **lst, t_sign **quote, char *str, int i)
{
	int			return_value;

	return_value = 0;
	if (str[i] == '\0')
		return (0);
	return_value = find_second_double(lst, quote, str, i);
	if (return_value > 0)
		return (return_value);
	return_value = find_second_single(lst, quote, str, i);
	if (return_value > 0)
		return (return_value);
	if ((*quote)->quote_type == SECOND_SINGLE_QUOTE)
	{
		ft_bzero(*quote, 1);
		return (1);
	}
	if ((*quote)->quote_type == SECOND_DOUBLE_QUOTE)
	{
		ft_bzero(*quote, 1);
		return (1);
	}
	ft_bzero(*quote, 1);
	return_value = double_or_first(quote, str, i);
	return (return_value);
}
