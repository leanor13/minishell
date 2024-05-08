/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:39:28 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/08 11:47:53 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO check with valgrind what happens if this is in the middle of the pipe

int	ft_exit(t_shell *shell, t_arg *command)
{
	int exit_status;
	int i;
	char 	**args = command->args_parsed; 
	
	exit_status = EXIT_SUCCESS;
    if (args[1] && args[2]) 
	{
        ft_putstr_nl("exit: too many arguments\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    if (args[1])
	{
		i = 0;
		while (i < ft_strlen(args[1]) && args[1][i] == ' ')
			i++;
		if (args[1][i] == '-' || args[1][i] == '+')
			i++;
		while (i < ft_strlen(args[1]))
		{
			if (!ft_isdigit(args[1][i]))
				return (EXIT_FAILURE);
			i++;
		}
        exit_status = ft_atoi(args[1]);
		if (exit_status < 0)
			exit_status = 0;
		if (exit_status > 255)
			exit_status = 255;
	}
	shell->exit_status = exit_status;
    return (exit_status);
}
