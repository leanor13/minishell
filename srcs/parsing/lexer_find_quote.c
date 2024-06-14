/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_find_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 16:06:34 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_firstquote(t_sign **lst, char *str, int i)
{
	if ((*lst)->quote_type != FIRST_DOUBLE_QUOTE)
	{
		if (str[i] == 34)
		{
			(*lst)->quote_type = FIRST_DOUBLE_QUOTE;
			return (1);
		}
	}
	if ((*lst)->quote_type != FIRST_SINGLE_QUOTE)
	{
		if (str[i] == 39)
		{
			(*lst)->quote_type = FIRST_SINGLE_QUOTE;
			return (1);
		}
	}
	return (0);
}

int	find_quote(t_sign **lst, char *str, int i)
{
	if ((*lst)->quote_type == FIRST_DOUBLE_QUOTE)
	{
		if (str[i] == 34)
		{
			(*lst)->quote_type = SECOND_DOUBLE_QUOTE;
			return (1);
		}
		else
			return (0);
	}
	if ((*lst)->quote_type == FIRST_SINGLE_QUOTE)
	{
		if (str[i] == 39)
		{
			(*lst)->quote_type = SECOND_SINGLE_QUOTE;
			return (1);
		}
		else
			return (0);
	}
	if (find_firstquote(lst, str, i))
		return (1);
	return (0);
}
