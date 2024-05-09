/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:15:37 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/09 15:24:44 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO: clean fd_out every time we run command with it

int	ft_env(t_shell *shell, t_arg *command)
{
	int		i;
	char 	**env = shell->env_2d;
	char 	**args = command->args_doublechar; 
	int 	fd_out = STDOUT_FILENO;

	i = 0;
	if (args && args[0] && args[1])
		return (ft_putstr_nl("env: No such file or directory", STDERR_FILENO), EXIT_FAILURE);
	while (env && env[i] != NULL)
	{
		if (*env[i] != '\0' && *env[i] != '=' && ft_strchr(env[i], '='))
			ft_putstr_nl(env[i], fd_out);
		i ++;
	}
	return (EXIT_SUCCESS);
}
