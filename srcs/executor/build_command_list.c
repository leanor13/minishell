/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:02:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/31 12:55:28 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*make_path(char *command, int dir_len, char *dir_start, bool is_end)
{
	char	*path_buf;
	int		buf_size;

	path_buf = ft_calloc((dir_len + ft_strlen(command) + 2), sizeof(char));
	if (!path_buf)
	{
		perror("Failed path buffer memory allocation");
		return (NULL);
	}
	if (is_end)
		buf_size = dir_len + ft_strlen(command) + 2;
	else
		buf_size = dir_len + 1;
	ft_strlcpy(path_buf, dir_start, buf_size);
	ft_strcat(path_buf, "/");
	ft_strcat(path_buf, command);
	return (path_buf);
}

static char	*find_path(char *command, char **envp)
{
	char	*command_path_buf;
	int		dir_len;
	char	*dir_start;
	bool	is_end;

	if (absolute_path(command))
		return (ft_strdup(command));
	dir_start = dir_start_calc(command, envp);
	if (!dir_start)
		return (NULL);
	is_end = false;
	while (!is_end)
	{
		dir_len = dir_len_count(dir_start);
		if (dir_len == ft_strlen(dir_start))
			is_end = true;
		command_path_buf = make_path(command, dir_len, dir_start, is_end);
		if (command_path_buf && access(command_path_buf, X_OK) == 0)
			return (command_path_buf);
		free(command_path_buf);
		if (!is_end)
			dir_start = ft_strchr(dir_start, ':') + 1;
	}
	ft_putstr_fd(command, STDERR_FILENO);
	return (ft_putstr_nl(": command not found", STDERR_FILENO), NULL);
}

static int	update_command(t_arg *command, t_shell *shell)
{
	int	i;

	if (!command->arguments)
		return (EXIT_FAILURE);
	command->command = command->arguments[0];
	if (check_built_in(command) == true)
		return (EXIT_SUCCESS);
	command->path = find_path(command->command, shell->env_2d);
	if (!command->path)
	{
		i = 0;
		while (command->arguments[i])
		{
			free(command->arguments[i]);
			i++;
		}
		free(command->arguments);
		command->arguments = NULL;
		command->command = NULL;
		command->built_in_fn = NULL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	build_command_list(t_shell *shell)
{
	int		i;
	int		command_count;
	t_arg	*curr_arg;

	command_count = args_count(shell->args_list);
	curr_arg = shell->args_list;
	i = 0;
	while (i < command_count)
	{
		if (curr_arg->arguments && curr_arg->arguments[0])
			update_command(curr_arg, shell);
		else
			ft_putstr_fd("Syntax error: empty command\n", STDERR_FILENO);
		i++;
		curr_arg = curr_arg->next;
	}
	return (EXIT_SUCCESS);
}
