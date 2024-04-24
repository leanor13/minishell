/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:14:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/24 13:16:20 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_env(t_shell *shell)
{
	// TODO
	return ;
}

void	parse_env(t_shell *shell, char **env)
{
	// TODO
	return ;
}

void	empty_user(t_shell *shell)
{
	// TODO  - handle case when getenv("USER") == NULL;
	return ;
}

int	init(t_shell *shell, char **env)
{
	if (!env || !*env)
	{
		shell->no_env = true;
		init_env(shell);
	}
	else
	{
		shell->no_env = false;
		shell->env = env;
		parse_env(shell, env);
	}
	if (getenv("USER") == NULL)
		empty_user(shell);
	shell->std_fds[0] = dup(STDIN_FILENO);
	shell->std_fds[1] = dup(STDOUT_FILENO);
	shell->std_fds[2] = dup(STDERR_FILENO);
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



//Replace the environment variables into a linked list so you can delete or add to them later using export and unset builtins. In addition to displaying them using env or export (without arguments) builtins. 
//https://github.com/fraqioui/minishell?tab=readme-ov-file#Initializing