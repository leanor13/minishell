/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/22 19:28:58 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	closed_quotes(char *str)
{
	int	i;
	int	n;
	
	i = 0;
	n = 0;
	while(str[i])
	{
		if(str[i] == 34 || str[i] == 39)
			n += 1;
		i++;
	}
	if(n % 2 == 0)
		return (true);
	else
		return (false);
}

int	skip_space(char *str, int i)
{
	int	nospace;

	nospace = i;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
			i++;
	if (nospace == i)
		return(0);
	return(i);
}

int shellcommand_scan(t_arg **lst, char *str, int i)
{
	int j;
	int type;

	j = 0;
	if(str[i] == '>' && str[i + 1] != '>')
	{
		j = 1;
		type = OUTPUT;
	}
	else if(str[i] == '<' && str[i + 1] != '<')
	{
		j = 1;
		type = INPUT;
	}
	else if(str[i] == '|' && str[i + 1] != '|')
	{
		j = 1;
		type = PIPE;
	}
	else if(str[i] == '<' && str[i + 1] == '<')
	{
		j = 2;
		type = HEREDOC;
	}
	else if(str[i] == '>' && str[i + 1] == '>')
	{
		j = 2;
		type = APPEND;
	}
	if(j == 1 || j == 2)	
	{
		append_node(lst, str, i, j, type);
		return (j);
	}
	else
		return(0);
}

int arg_scan(t_arg **lst, char *str, int i)
{
	int j;
	int type;
	int start;

	start = i;
	j = 0;
	type = ARG;
	// while(str[i] == (str[i] == 34 || str[i] == 39))LATER
	// 	i++;
	// if((str[i - 1] == 34 || str[i - 1] == 39))LATER
	// {
	// 	while(str[i])
	// 	{
	// 		if((str[i - 1] == 34 || str[i - 1] == 39))
	// 			break ;
	// 		i++;
	// 		j++;
	// 	}
	// 	while(str[i])
	// 	{
	// 		if(skip_space(str, i))
	// 			break ;
	// 		i++;
	// 		j++;
	// 	}
	// }
	// else
	// {
	while(str[i])
	{
		if(skip_space(str, i))
			break ;
		i++;
		j++;
	}
	//}
	append_node(lst, str, start, j, type);
	return (j);
}

t_arg	*ft_lexer(char *str)
{
	t_arg *lst;
	int	i;
	
	lst = NULL;
	i = 0;
	// if(!closed_quotes(str))THIS PART LATER
	// 	return (NULL); //YULIA maybe error for here? instead of return
	while(str[i])
	{
		i += skip_space(str, i);// everytime when it is a space
		i += shellcommand_scan(&lst, str, i);
		i += arg_scan(&lst, str, i);
		i++;
	}
	return(lst);
}
