/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:14:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/29 17:25:11 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_env(t_shell *shell)
{
	// TODO
	shell->env_original = NULL;
	shell->env_shell = NULL;
	return ;
}

void	print_env(t_env *env)
{
	int		i = 0;
	t_env	*current;

	current = env;
	while (current)
	{
		// TODO remove printf
		printf("%d: %s = %s\n", i, current->var_name, current->var_value);
		i ++;
		current = current->next;
	}
}

void	empty_user(t_shell *shell)
{
	// TODO  - handle case when getenv("USER") == NULL;
	(void)shell;
	return ;
}

int	add_back_env(t_env **head, char *var_name, char *var_value)
{
	t_env	*curr;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (EXIT_FAILURE);
	node->var_name = ft_strdup(var_name);
	if (!node->var_name)
		return (free(node), EXIT_FAILURE);
	node->var_value = ft_strdup(var_value);
	if (!node->var_value)
	{
		free(node->var_name);
		free(node);
		return (EXIT_FAILURE);
	}
	node->next = NULL;
	if (!(*head))
	{
		*head = node;
		return (EXIT_SUCCESS);
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = node;
	return (EXIT_SUCCESS);
}

int	parse_env(t_shell *shell, char **env)
{
	int		i;
	char	*var_name;
	char	*var_value;
	char	*equal;

	i = 0;
	shell->env_shell = NULL;
	while (env[i])
	{
		equal = ft_strchr(env[i], '=');
		if (equal != NULL)
		{
			*equal = '\0';
			var_value = equal + 1;
		}
		else
			var_value = NULL;
		var_name = env[i];
		if (add_back_env(&shell->env_shell, var_name, var_value) != EXIT_SUCCESS)
		{
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		i ++;
	}
	return (EXIT_SUCCESS);
}

void	handle_env(t_shell *shell, char **env)
{
	if (!env || !*env)
	{
		shell->no_env = true;
		new_env(shell);
	}
	else
	{
		shell->no_env = false;
		shell->env_original = env;
		if (parse_env(shell, env) != EXIT_SUCCESS)
		{
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
	shell->args_list = NULL;
	shell->here_doc = NULL;
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



//Replace the environment variables into a linked list so you can delete or add to them later using export and unset builtins. In addition to displaying them using env or export (without arguments) builtins. 
//https://github.com/fraqioui/minishell?tab=readme-ov-file#Initializing