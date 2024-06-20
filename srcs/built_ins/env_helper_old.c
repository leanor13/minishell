/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper_old.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:31:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/20 15:27:37 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_len_count(t_env *env_lst)
{
	int	i;

	i = 0;
	while (env_lst != NULL)
	{
		i++;
		env_lst = env_lst->next;
	}
	return (i);
}

int	setup_env_2d_array(t_env *env_lst, char ***env_2d)
{
	free_string_array(env_2d);
	*env_2d = ft_calloc((env_len_count(env_lst) + 1), sizeof(char *));
	if (!*env_2d)
	{
		perror("calloc error");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	protect_malloc(char *str, char ***env_2d)
{
	if (!str)
	{
		free_string_array(env_2d);
		perror("malloc error");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	convert_env_lst_to_2d(t_env *env_lst, char ***env_2d)
{
	char	*temp;
	int		i;

	if (setup_env_2d_array(env_lst, env_2d) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	i = 0;
	while (env_lst)
	{
		temp = NULL;
		if (env_lst->var_value && env_lst->var_name)
		{
			temp = ft_strjoin(env_lst->var_name, "=");
			if (protect_malloc(temp, env_2d) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			(*env_2d)[i] = ft_strjoin(temp, env_lst->var_value);
			if (protect_malloc((*env_2d)[i], env_2d) != EXIT_SUCCESS)
				return (free(temp), EXIT_FAILURE);
		}
		else
			(*env_2d)[i] = ft_strdup(env_lst->var_name);
		i++;
		free(temp);
		env_lst = env_lst->next;
	}
	return (EXIT_SUCCESS);
}

int	update_env_2d(t_shell *shell)
{
	if (convert_env_lst_to_2d(shell->env_list, &shell->env_2d) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
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
	if (!node->var_name)
		return (free(node), EXIT_FAILURE);
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
	else
		node->var_value = NULL;
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
	char	*env_copy;

	i = 0;
	shell->env_list = NULL;
	while (env[i])
	{
		env_copy = strdup(env[i]);
		if (!env_copy)
		{
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		equal = strchr(env_copy, '=');
		if (equal != NULL)
		{
			*equal = '\0';
			var_value = equal + 1;
		}
		else
			var_value = NULL;
		var_name = env_copy;
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
