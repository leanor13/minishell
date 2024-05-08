/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:09:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/08 11:41:12 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command_list(t_arg **command_list)
{
	int		j;
	t_arg	*current;
	t_arg	*next;

	current = *command_list;
	while (current)
	{
		j = 0;
		while (current->args_parsed && current->args_parsed[j])
		{
			free(current->args_parsed[j]);
			current->args_parsed[j] = NULL;
			j++;
		}
		free(current->args_parsed);
		current->args_parsed = NULL;
		//free(current->args);
		current->args = NULL;
		free(current->path);
		current->path = NULL;
		next = current->next;
		//free(current);
		current = NULL;
		current = next;
	}
	*command_list = NULL;
	close_all_protected();
}

void	dup_close(int fd, int reference)
{
	if (fd != reference)
	{
		if (dup2(fd, reference) == -1)
            perror("dup_close failure");
		ft_close(fd);
	}
}

