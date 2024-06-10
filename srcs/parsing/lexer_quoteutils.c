/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quoteutils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/10 15:50:54 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			return(0);
	}
	if ((*lst)->quote_type == FIRST_SINGLE_QUOTE)
	{
		if (str[i] == 39)
		{
			(*lst)->quote_type = SECOND_SINGLE_QUOTE;
			return (1);
		}
		else
			return(0);
	}
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

int	handle_quotestring(t_arg **lst, t_sign **quote, char *str, int i)
{
	t_append	info;

	if (str[i] == '\0')
		return (0);
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
	if ((str[i] == 34 && str[i + 1] == 34) ||
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

// int	find_firstquote(t_sign **lst, char *str, int i)
// {
// 	if ((*lst)->quote_type != FIRST_DOUBLE_QUOTE)
// 	{
// 		if (str[i] == 34)
// 		{
// 			(*lst)->quote_type = FIRST_DOUBLE_QUOTE;
// 			return (1);
// 		}
// 	}
// 	if ((*lst)->quote_type != FIRST_SINGLE_QUOTE)
// 	{
// 		if (str[i] == 39)
// 		{
// 			(*lst)->quote_type = FIRST_SINGLE_QUOTE;
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// int	find_quote(t_sign **lst, char *str, int i)
// {
// 	if ((*lst)->quote_type == FIRST_DOUBLE_QUOTE)
// 	{
// 		if (str[i] == 34)
// 		{
// 			(*lst)->quote_type = SECOND_DOUBLE_QUOTE;
// 			return (1);
// 		}
// 	}
// 	if ((*lst)->quote_type == FIRST_SINGLE_QUOTE)
// 	{
// 		if (str[i] == 39)
// 		{
// 			(*lst)->quote_type = SECOND_SINGLE_QUOTE;
// 			return (1);
// 		}
// 	}
// 	if ((*lst)->quote_type != FIRST_DOUBLE_QUOTE || \
// 	(*lst)->quote_type != FIRST_SINGLE_QUOTE)
// 	{
// 		if (find_firstquote(lst, str, i))
// 			return (1);
// 	}
// 	return (0);
// }