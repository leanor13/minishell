/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:48 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/31 18:22:38 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*envp_path(char **envp)
{
	if (!envp)
	{
		ft_putstr_nl("Empty environment", STDERR_FILENO);
		return (NULL);
	}
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*dir_start_calc(char *command, char **envp)
{
	char	*dir_start;

	dir_start = envp_path(envp);
	if (!dir_start)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		return (ft_putstr_fd(EMPTY_ENV, STDERR_FILENO), NULL);
	}
	return (dir_start);
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
	if (*command == '/' || (*command == '.' && *(command + 1) == '/'))
	{
		if (access(command, X_OK) == 0)
			return (command);
		else
		{
			ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
			ft_putstr_nl(command, STDERR_FILENO);
			return (NULL);
		}
	}
	return (NULL);
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
