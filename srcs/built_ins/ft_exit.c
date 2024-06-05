/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:39:28 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/05 18:15:21 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO check with valgrind what happens if this is in the middle of the pipe

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v')
		return (1);
	return (0);
}

int	is_digit_string(char *str)
{
	int	i;
	int	start;

	i = 0;
	if (ft_strlen(str) > 18)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	start = i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i > start);
}

void	ft_put_error_message(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

int	ft_exit(t_shell *shell, t_arg *command)
{
	char	**args;
	int		exit_status;

	args = command->arguments;
	exit_status = EXIT_SUCCESS;
	if (args[1] && args[2])
	{
		ft_putstr_nl("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (args[1])
	{
		if (!is_digit_string(args[1]))
		{
			ft_put_error_message(args[1]);
			shell->exit_status = 2;
			return (2);
		}
		exit_status = ft_atoi(args[1]) % 256;
		if (exit_status < 0)
			exit_status += 256;
	}
	shell->exit_status = exit_status;
	shell->should_exit = true;
	return (exit_status);
}
