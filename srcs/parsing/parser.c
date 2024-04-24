/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/24 15:46:07 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void lst_delone(void)
{
	return ;
}

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