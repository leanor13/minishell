/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:14:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/07 12:27:29 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	save_2d_env(char **arr, char ***dest)
{
	int		len_arr;
	int		i;

	i = 0;
	len_arr = 0;
	if (!arr)
	{
		*dest = ft_calloc(1, sizeof(char *));
		if (!*dest)
			return (ft_putstr_nl("malloc failure", STDERR_FILENO), EXIT_FAILURE);
		**dest = NULL;
		return (EXIT_SUCCESS);
	}
	while (arr[len_arr])
		len_arr ++;
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
		i ++;
	}
	return (EXIT_SUCCESS);
}

void	new_env(t_shell *shell)
{
	// TODO
	shell->env_2d = NULL;
	shell->env_list = NULL;
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
	shell->env_list = NULL;
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
		if (add_back_env(&shell->env_list, var_name, var_value) != EXIT_SUCCESS)
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
		if (save_2d_env(env, &shell->env_2d) != EXIT_SUCCESS)
		{
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
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
	shell->std_fds[0] = dup2(STDIN_FILENO, 0);
	shell->std_fds[1] = dup2(STDOUT_FILENO, 1);
	shell->std_fds[2] = dup2(STDERR_FILENO, 2);
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