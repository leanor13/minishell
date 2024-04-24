/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:11:30 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/24 17:06:42 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_shell(t_shell *shell)
{
	// TODO
	(void)shell;
	// clean shell_env, including all nodes, + all names and values.
	return ;
}

void	free_string_array(char ***str_arr)
{
	int	i;

	if (!*str_arr)
		return ;
	i = 0;
	while (*str_arr[i])
	{
		free(*str_arr[i]);
		*str_arr[i] = NULL;
		i ++;
	}
	free(*str_arr);
	*str_arr = NULL;
}
free_envs;
free_args;