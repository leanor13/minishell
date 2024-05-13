/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/13 23:22:04 by thuy-ngu         ###   ########.fr       */
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
	int j;

	j = 0;
	nospace = i;
	//while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
	while(str[i] == ' ')
	{
			i++;
			j++;
	}
	if (nospace == i)
		return(0);
	return(j);
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
	if(str[i] == '\0')
		return(j);
	if(str[i] == '|' || str[i] == '<' || str[i] == '>')
		return(shellcommand_scan(lst, str, i));
	while(str[i])
	{
		// if(str[i] != '<' || str[i] != '>') some protection if it is only > <
		// 	return(j);
		if(str[i] == '|' || str[i] == '<' || str[i] == '>')
			break;
		if(skip_space(str, i))
			break ;
		i++;
		j++;
	}
	//}
	append_node(lst, str, start, j, type);
	return (j);
}

t_arg	*ft_lexer(char *str, t_arg *lst)
{
	int	i;

	i = 0;
	// if(!closed_quotes(str))THIS PART LATER
	// 	return (NULL); //YULIA maybe error for here? instead of return
	//IT IS NOT GOING TO WORK JUST WITH THIS >> << OR THIS OR IF IT IS AT THE END 
	while(str[i])
	{
		i += skip_space(str, i);// everytime when it is a space
		i += handle_quotestring(&quote, str, i);
		i += shellcommand_scan(&lst, str, i);
		i += skip_space(str, i);
		i += arg_scan(&lst, str, i);
		//i++;
	}
	return(lst);
}

// minishell$< > < >
// <
// 1
// >
// 5
// <
// 1
// >
// 5 this case i snot working