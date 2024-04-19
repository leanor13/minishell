/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:35:34 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/19 16:54:34 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_built_in(t_command *command)
{
	if (ft_strcmp(command->command, "pwd") == 0)
		return(command->built_in_fn = ft_pwd, true);
	else if (ft_strcmp(command->command, "env") == 0)
		return(command->built_in_fn = ft_env, true);
	else if (ft_strcmp(command->command, "echo") == 0)
		return(command->built_in_fn = ft_echo, true);
	else if (ft_strcmp(command->command, "unset") == 0)
		return(command->built_in_fn = ft_unset, true);
	return (false);
}