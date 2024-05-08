/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:46:27 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/08 13:22:37 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO handle $variable

static void handle_quotes_and_special_chars(char *arg, int len_arg, int fd_out) 
{
	bool	in_quote;
	int		i;

	i = 0;
	in_quote = false;
	while (i < len_arg)
	{
		if (arg[i] == '\'' && !in_quote) 
			in_quote = true;
		else if (arg[i] == '\'' && in_quote)
			in_quote = false;
		else if (arg[i] == '"' && !in_quote) 
			in_quote = true;
		else if (arg[i] == '"' && in_quote) 
			in_quote = false;
		if (!in_quote && (arg[i] == '\\' || arg[i] == ';'))
			continue;
		ft_putchar_fd(arg[i], fd_out);
		i ++;
	}
}

static void	echo_arg(char *arg, t_env *env_lst, int fd_out)
{
	int	len_arg;
	char	*var_value;

	len_arg = ft_strlen(arg);
	if (!arg || !arg[0])
		return ;
	if (arg[0] == '$')
	{
		var_value = env_find_var(env_lst, arg + 1)->var_value;
		ft_putstr_fd(var_value, fd_out);
	}
	else
		handle_quotes_and_special_chars(arg, len_arg, fd_out);
}

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

int	ft_echo(t_shell *shell, t_arg *command)
{
	bool	new_line;
	int		i;
	char 	**args = command->args_parsed; 
	int 	fd_out = STDOUT_FILENO;

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
		echo_arg(args[i], shell->env_list, fd_out);
		i ++;
		if (args[i] != NULL)
			ft_putchar_fd(' ', fd_out);
	}
	if (new_line)
		ft_putchar_fd('\n', fd_out);
	return (EXIT_SUCCESS);
}
