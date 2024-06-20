/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:15:47 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/20 11:16:39 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	apply_var_value(char *var_value, t_env *node)
{
	if (var_value)
	{
		node->var_value = ft_strdup(var_value);
		if (!node->var_value)
		{
			free(node->var_name);
			free(node);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	add_back_env(t_env **head, char *var_name, char *var_value)
{
	t_env	*curr;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (EXIT_FAILURE);
	node->var_name = ft_strdup(var_name);
	node->var_value = NULL;
	if (!node->var_name)
		return (free(node), EXIT_FAILURE);
	if (apply_var_value(var_value, node) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
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

int	init_parse_env(char **env, char **env_copy, int i)
{
	*env_copy = strdup(env[i]);
	if (!*env_copy)
	{
		perror("Failed to duplicate environment string");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parse_single_env_entry(char *env_copy, char **var_name, char **var_value)
{
	char	*equal;

	equal = strchr(env_copy, '=');
	if (equal != NULL)
	{
		*equal = '\0';
		*var_value = equal + 1;
	}
	*var_name = env_copy;
	return (EXIT_SUCCESS);
}

int	parse_env(t_shell *shell, char **env)
{
	int		i;
	char	*var_name;
	char	*var_value;
	char	*env_copy;

	shell->env_list = NULL;
	i = 0;
	while (env[i])
	{
		if (init_parse_env(env, &env_copy, i) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (parse_single_env_entry(env_copy, &var_name,
				&var_value) != EXIT_SUCCESS)
			return (free(env_copy), EXIT_FAILURE);
		if (add_back_env(&shell->env_list, var_name, var_value) != EXIT_SUCCESS)
		{
			free(env_copy);
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		free(env_copy);
		i++;
	}
	return (EXIT_SUCCESS);
}