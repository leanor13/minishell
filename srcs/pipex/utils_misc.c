/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:48 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/28 12:10:00 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	dir_len_count(char *dir_start)
{
	int	dir_len;

	if (ft_strchr(dir_start, ':') != NULL)
		dir_len = ft_strchr(dir_start, ':') - dir_start;
	else
	{
		dir_len = ft_strlen(dir_start);
	}
	return (dir_len);
}

char	*absolute_path(char *command)
{
	if (*command == '/')
	{
		if (access(command, X_OK) == 0)
			return (command);
		else
			return (ft_putstr_fd("Wrong command path\n", STDERR_FILENO), NULL);
	}
	return (NULL);
}

void	validate_params(int ac, char **av)
{
	if (ac < 5 || !av || !av[1]
		|| (ft_strcmp(av[1], "here_doc") == 0 && ac < 6))
	{
		ft_putstr_fd(WRONG_ARG_NUM, STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
}

int	args_count(t_arg *args_list)
{
	int	i;

	i = 0;
	while (args_list != NULL)
	{
		i++;
		args_list = args_list->next;
	}
	return (i);
}
