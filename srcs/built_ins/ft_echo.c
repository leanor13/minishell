/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:46:27 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/05 19:05:31 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_content(char *arg, int len_arg, int fd_out)
{
	int		i;

	i = 0;
	while (i < len_arg)
	{
		ft_putchar_fd(arg[i], fd_out);
		i++;
	}
}

static void	echo_arg(char *arg, int fd_out)
{
	int		len_arg;

	len_arg = ft_strlen(arg);
	if (!arg || !arg[0])
		return ;
	print_content(arg, len_arg, fd_out);
}

static void	process_escape_sequences(char *str)
{
	char	*dest;

	dest = str;
	while (*str)
	{
		if (*str == '\\' && *(str + 1) != '\0')
		{
			if (*(str + 1) == 'n')
			{
				*dest++ = '\n';
				str += 2;
			}
			else if (*(str + 1) == 't')
			{
				*dest++ = '\t';
				str += 2;
			}
			else
				*dest++ = *str++;
		}
		else
			*dest++ = *str++;
	}
	*dest = '\0';
}

int	ft_echo(t_shell *shell, t_arg *command)
{
	bool	new_line;
	int		i;
	char	**args;

	args = command->arguments;
	(void)shell;
	new_line = true;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		new_line = false;
		args++;
	}
	i = 1;
	while (args[i] != NULL)
	{
		process_escape_sequences(args[i]);
		echo_arg(args[i], STDOUT_FILENO);
		i++;
		if (args[i] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
