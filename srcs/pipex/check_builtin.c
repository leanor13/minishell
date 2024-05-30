/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:35:34 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/28 12:10:25 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_built_in(t_arg *command)
{
	if (ft_strcmp(command->command, "pwd") == 0)
		return (command->built_in_fn = ft_pwd, true);
	else if (ft_strcmp(command->command, "env") == 0)
		return (command->built_in_fn = ft_env, true);
	else if (ft_strcmp(command->command, "echo") == 0)
		return (command->built_in_fn = ft_echo, true);
	else if (ft_strcmp(command->command, "unset") == 0)
		return (command->built_in_fn = ft_unset, true);
	else if (ft_strcmp(command->command, "exit") == 0)
		return (command->built_in_fn = ft_exit, true);
	else if (ft_strcmp(command->command, "cd") == 0)
		return (command->built_in_fn = ft_cd, true);
	else if (ft_strcmp(command->command, "export") == 0)
		return (command->built_in_fn = ft_export, true);
	return (false);
}
