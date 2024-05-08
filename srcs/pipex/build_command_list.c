/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:02:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/08 19:45:42 by yioffe           ###   ########.fr       */
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

static char	*envp_path(char **envp)
{
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp ++;
	}
	return (NULL);
}

static char	*find_path(char *command, char **envp)
{
	char	*command_path_buf;
	int		dir_len;
	char	*dir_start;
	bool	is_end;

	if (absolute_path(command))
		return (ft_strdup(command));
	dir_start = envp_path(envp);
	if (!dir_start)
		return (ft_putstr_fd(EMPTY_ENV, STDERR_FILENO), NULL);
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
	return (ft_putstr_fd("Failed to find command path\n", STDERR_FILENO), NULL);
}

static int	update_command(t_arg *command, t_shell *shell)
{
	int	i;

	// add here error messages
	//command->args_parsed = ft_split_pipex(command->args, ' ');
	save_2d_env(command->args_doublechar, &command->args_parsed);
	if (!command->args_parsed)
		return (EXIT_FAILURE);
	command->command = command->args_parsed[0];
	if (check_built_in(command) == true)
		return (EXIT_SUCCESS);
	command->path = find_path(command->command, shell->env_2d);
	if (!command->path)
	{
		i = 0;
		while (command->args_parsed[i])
		{
			free(command->args_parsed[i]);
			i++;
		}
		free(command->args_parsed);
		command->args_parsed = NULL;
		//free(command->old_args_old);
		//command->old_args_old = NULL;
		command->command = NULL;
		command->built_in_fn = NULL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	args_count(t_arg *args_list)
{
	int i;

	i = 0;
	while (args_list != NULL)
	{
		i ++;
		args_list = args_list->next;
	}
	return (i);
}

int	build_command_list(t_shell *shell)
{
	int			i;
	int			command_count;
	t_arg		*curr_arg;

	command_count = args_count(shell->args_list);
	curr_arg = shell->args_list;
	i = 0;
	while (i < command_count)
	{
		if (curr_arg->args_doublechar && curr_arg->args_doublechar[0])
		{
			// TODO in case of empty/failed update we can clean cmd, and proceed to next ones
			if (update_command(curr_arg, shell) != EXIT_SUCCESS)
				{
					free_command_list(&shell->args_list);
					return (EXIT_FAILURE);
				}
		}
		else
			return (ft_putstr_fd("Syntax error: empty command\n", STDERR_FILENO), EXIT_FAILURE);
		i++;
		curr_arg = curr_arg->next;
	}
	return (EXIT_SUCCESS);
}
