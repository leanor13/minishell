/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:09:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/19 18:01:29 by yioffe           ###   ########.fr       */
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
		while (current->arguments && current->arguments[j])
		{
			free(current->arguments[j]);
			current->arguments[j] = NULL;
			j++;
		}
		free(current->arguments);
		current->arguments = NULL;
		free(current->path);
		current->path = NULL;
		next = current->next;
		current = NULL;
		current = next;
	}
	*command_list = NULL;
}

void	dup_close(int fd, int reference)
{
	if (fd != reference && fd >= 0 && reference >= 0)
	{
		if (dup2(fd, reference) == -1)
			perror("dup_close failure");
		ft_close(fd);
	}
}
