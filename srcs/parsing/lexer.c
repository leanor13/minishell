/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/17 22:23:36 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_space(char *str, int i)
{
	int	nospace;
	int j;

	j = 0;
	if(str[i] == '\0')
		return(j);
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
	if(str[i] == '\0')
		return(j);
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
	else if(str[i] == '|' && str[i + 1] == '|')
	{
		j = 2;
		type = DOUBLE_PIPE;
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

int	find_quote(t_sign **lst, char *str, int i)
{
	if ((*lst)->quote_type == FIRST_DOUBLE_QUOTE)
	{
		if (str[i] == 34)
		{
			(*lst)->quote_type = SECOND_DOUBLE_QUOTE;
			return(1);
		}
		else
			return(0);
	}
	else if ((*lst)->quote_type == FIRST_SINGLE_QUOTE)
	{
		if (str[i] == 39)
		{
			(*lst)->quote_type = SECOND_SINGLE_QUOTE;
			return(1);
		}
		else
			return(0);
	}
	else if ((*lst)->quote_type != FIRST_DOUBLE_QUOTE)
	{
		if (str[i] == 34)
		{
			(*lst)->quote_type = FIRST_DOUBLE_QUOTE;
			return(1);
		}
		else
			return(0);
	}
	else if ((*lst)->quote_type != FIRST_SINGLE_QUOTE)
	{
		if (str[i] == 39)
		{
			(*lst)->quote_type = FIRST_SINGLE_QUOTE;
			return(1);
		}
		else
			return(0);
	}
	return(0);
}

int	handle_quotestring(t_arg **lst, t_sign **quote, char *str, int i)
{
	if(str[i] == '\0')
		return(0);
	if((*quote)->quote_type == FIRST_SINGLE_QUOTE || (*quote)->quote_type == FIRST_DOUBLE_QUOTE)
	{
		if((str[i] == 34 && str[i + 1] == 34) || (str[i] == 39 && str[i + 1] == 39))
		{
			*quote = ft_calloc(1, sizeof(t_sign));
			append_node(lst, "\0", 0, 1, ARG);// MAKE AN EMTPY STRING HERE
			return(2);
		}
		else
			return(0);
	}
	if((*quote)->quote_type == SECOND_SINGLE_QUOTE || (*quote)->quote_type == SECOND_DOUBLE_QUOTE)
	{
			*quote = ft_calloc(1, sizeof(t_sign));
			//append_node(lst, "\0", 0, 1, ARG);// MAKE AN EMTPY STRING HERE
			return(1);
	}
	*quote = ft_calloc(1, sizeof(t_sign));
	if ((str[i] == 34 && str[i + 1] == 34) || (str[i] == 39 && str[i + 1] == 39))
	{
		(*quote)->quote_type = 0;
		// append_node(lst, " ", i, 1, ARG);
		return(2);
	}
	if (str[i] == 34)
	{
		(*quote)->quote_type = FIRST_DOUBLE_QUOTE;
		return(1);
	}
	if (str[i] == 39)
	{
		(*quote)->quote_type = FIRST_SINGLE_QUOTE;
		return(1);
	}
	return(0);
}

int arg_scan(t_arg **lst, char *str, int i, t_sign **quote)
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
		if((*quote)->quote_type == 0)
		{
		 	if(skip_space(str, i))
		 		break ;
		}
		if((*quote)->quote_type == 0)
		{
		 	if(str[i] == '|' || str[i] == '<' || str[i] == '>')
				break ;
		}
		if(find_quote(quote, str, i) == 1)
		  	break ;
		i++;
		j++;
	}
	append_node(lst, str, start, j, type);
	return (j);
}

t_arg	*ft_lexer(char *str, t_arg *lst)
{
	int	i;
	t_arg	*head;
	i = 0;
	t_sign	*quote;
	if (!str || !*str)
		return (NULL);
	// if(!closed_quotes(str))// IT IS MORE COMPLEX THAN JUST THIS
	// 	return (NULL);
	quote = ft_calloc(1, sizeof(t_sign));
	// 	return (NULL); //YULIA maybe error for here? instead of return
	//IT IS NOT GOING TO WORK JUST WITH THIS >> << OR THIS OR IF IT IS AT THE END 
	while(str[i])
	{
		i += skip_space(str, i);// everytime when it is a space
		i += handle_quotestring(&lst, &quote, str, i);
		
		i += shellcommand_scan(&lst, str, i);
		if(quote->quote_type == 0)
			i += skip_space(str, i);
		i += arg_scan(&lst, str, i, &quote);
		// if(!ft_strcmp(lst->str, "echo"))
		// 	printf("ITT\n");
		//i++;
	}
	head = lst;
	if(quote->quote_type == FIRST_SINGLE_QUOTE || quote->quote_type == FIRST_DOUBLE_QUOTE)// YULIA should something if it is unclosed quote 
	{
		free(head);
		ft_printf("bash: syntax error: UNCLOSED_QUOTE\n");
	 	return(NULL);
	}
	return(lst);
}
