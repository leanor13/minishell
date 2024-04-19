/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:46:27 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/19 19:43:05 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO handle $variable

static void	process_escape_sequences(char *str)
{
	char	*src;
	char	*dest;
	
	if (str == NULL)
		return;
	src = str;
	dest = str;
	while (*src)
	{
		if (*src == '\\' && *(src + 1) != '\0')
		{
			if (*(src + 1) == 'n')
			{
				*dest++ = '\n';
				src += 2;
			}
			else if (*(src + 1) == 't')
			{
				*dest++ = '\t';
				src += 2;
			}
			else
				*dest++ = *src++;
		}
		else
			*dest++ = *src++;
	}
	*dest = '\0';
}
// TODO - handle quotes if needed? or check if it's part of parser

int	ft_echo(char **env, char **args, int fd_out)
{
	bool	new_line;
	int		i;

	(void)env;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		new_line = false;
		args ++;
	}
	else
		new_line = true;
	i = 1;
	while (args[i] != NULL)
	{
		process_escape_sequences(args[i]);
		ft_putstr_fd(args[i], fd_out);
		i ++;
		if (args[i] != NULL)
			ft_putchar_fd(' ', fd_out);
	}
	if (new_line)
		ft_putchar_fd('\n', fd_out);
	return (EXIT_SUCCESS);
}
