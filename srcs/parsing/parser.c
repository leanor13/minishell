/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/22 20:17:27 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg *ft_parser(t_arg *lst)
{
	while(lst)
	{
		
		lst->in_file = NULL;
		lst->out_file = NULL;
		
		if(lst->type == ARG)
			lst = lst->next;
		if(lst->type == OUTPUT)
		{
			lst_delone();
			lst = lst->next;
			lst->out_file = lst->str;
			lst->str = NULL;
			lst->here_doc = NULL;
			lst->append = false;
		}
		if(lst->type == INPUT)
		{
			lst_delone();
			lst = lst->next;
			lst->in_file = lst->str;
			lst->str = NULL;
			lst->here_doc = NULL;
			lst->append = false;
		}
		if(lst->type == HEREDOC)
		{
			lst_delone();
			lst = lst->next;
			lst->in_file = lst->str;
			lst->str = NULL;
			lst->here_doc = NULL;
			lst->append = false;
		}
		if(lst->type == APPEND)
		{
			lst_delone();
			lst = lst->next;
			lst->in_file = lst->str;
			lst->str = NULL;
			lst->here_doc = NULL;
			lst->append = false;
		}
		lst = lst->next;
		lst = lst->next;
		if(lst->type == PIPE)
		{
			
		}
	}
	//if delone, del the >, <, >>, << split, if pipe
	return(lst);
}