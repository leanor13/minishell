/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:14:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/29 17:37:24 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	save_2d_env(char **arr, char ***dest)
{
	int	len_arr;
	int	i;

	i = 0;
	len_arr = 0;
	if (!arr)
	{
		*dest = ft_calloc(1, sizeof(char *));
		if (!*dest)
			return (ft_putstr_nl("malloc failure", STDERR_FILENO),
				EXIT_FAILURE);
		**dest = NULL;
		return (EXIT_SUCCESS);
	}
	while (arr[len_arr])
		len_arr++;
	*dest = ft_calloc((len_arr + 1), sizeof(char *));
	if (!*dest)
		return (ft_putstr_nl("malloc failure", STDERR_FILENO), EXIT_FAILURE);
	while (arr[i])
	{
		(*dest)[i] = ft_strdup(arr[i]);
		if (!(*dest)[i])
		{
			ft_putstr_nl("malloc failure", STDERR_FILENO);
			return (free_string_array(dest), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	new_env(t_shell *shell)
{
	char	*default_env[4];

	default_env[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	default_env[1] = "PWD=/";
	default_env[2] = "USER=evaluator";
	default_env[3] = NULL;
	if (save_2d_env(default_env, &shell->env_2d) != EXIT_SUCCESS)
	{
		ft_putstr_fd("Failed to initialize default environment", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (parse_env(shell, shell->env_2d) != EXIT_SUCCESS)
	{
		ft_putstr_fd(ENV_PARSING, STDERR_FILENO);
		free_shell(shell);
		exit(EXIT_FAILURE);
	}
}

void	empty_user(t_shell *shell)
{
	t_arg	*cmd;

	if (getenv("USER") == NULL && !env_find_var(shell->env_list, "USER"))
	{
		cmd = ft_calloc(1, sizeof(t_arg));
		if (!cmd)
		{
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		cmd->arguments = (char *[]){"export", "USER=evaluator", NULL};
		if (ft_export(shell, cmd) != EXIT_SUCCESS)
		{
			ft_putstr_fd("Failed to set default user environment variable",
				STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		free(cmd);
		ft_putstr_fd("Environment variable 'USER' set to 'evaluator'\n",
			STDOUT_FILENO);
	}
}

void	handle_env(t_shell *shell, char **env)
{
	if (!env || !*env)
	{
		shell->no_env = true;
		new_env(shell);
		env = shell->env_2d;
	}
	else
	{
		shell->no_env = false;
		if (save_2d_env(env, &shell->env_2d) != EXIT_SUCCESS)
		{
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		if (parse_env(shell, env) != EXIT_SUCCESS)
		{
			ft_putstr_fd(ENV_PARSING, STDERR_FILENO);
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
	}
	if (getenv("USER") == NULL)
		empty_user(shell);
	return ;
}

int	init_shell(t_shell *shell, char **env)
{
	handle_env(shell, env);
	shell->std_fds[0] = dup(STDIN_FILENO);
	shell->std_fds[1] = dup(STDOUT_FILENO);
	shell->std_fds[2] = dup(STDERR_FILENO);
	shell->here_doc_fd = 0;
	shell->args_list = NULL;
	shell->here_doc = false;
	shell->should_exit = false;
	shell->exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}

// if (getenv("USER") == NULL)// ASK YULIA
// 	init_missing_environment(shell, env);
// else
// {
// 	shell->envless = FALSE;
// 	shell->color_codes = TRUE;
// 	shell->env_head = init_env(env);
// 	shell->user_name = getenv("USER");
// 	shell->cmd_paths = ft_split(get_path(env), ':');
// }https://github.com/zstenger93/minishell/blob/master/src/init/init.c#L15

// Replace the environment variables into a linked list so you can delete or add to them later using export and unset builtins. In addition to displaying them using env or export (without arguments) builtins.
// https://github.com/fraqioui/minishell?tab=readme-ov-file#Initializing