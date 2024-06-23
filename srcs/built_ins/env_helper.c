/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:31:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/23 13:44:52 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_join_validator(char **dest, char *s1, char *s2, char ***env_2d)
{
	*dest = ft_strjoin(s1, s2);
	if (!*dest)
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

	i = 0;
	free_string_array(env_2d);
	*env_2d = ft_calloc((env_len_count(env_lst) + 1), sizeof(char *));
	if (!*env_2d)
		return (EXIT_FAILURE);
	while (env_lst)
	{
		temp = NULL;
		(*env_2d)[i] = NULL;
		if (env_lst->var_name)
		{
			if (ft_join_validator(&temp, env_lst->var_name, "=", env_2d) != 0)
				return (EXIT_FAILURE);
			if (ft_join_validator(&(*env_2d)[i], temp, env_lst->var_value, \
				env_2d) != 0)
				return (free(temp), EXIT_FAILURE);
		}
		i++;
		free(temp);
		env_lst = env_lst->next;
	}
	return (EXIT_SUCCESS);
}

int	add_back_env(t_env **head, char *var_name, char *var_value)
{
	t_env	*curr;
	t_env	*node;

	node = ft_calloc(sizeof(t_env), 1);
	if (!node)
		return (EXIT_FAILURE);
	node->var_name = ft_strdup(var_name);
	if (!node->var_name)
		return (free(node), EXIT_FAILURE);
	node->var_value = NULL;
	if (var_value)
	{
		node->var_value = ft_strdup(var_value);
		if (!node->var_value)
		{
			free(node->var_name);
			return (free(node), EXIT_FAILURE);
		}
	}
	if (!(*head))
		return (*head = node, EXIT_SUCCESS);
	curr = *head;
	while (curr->next)
		curr = curr->next;
	return (curr->next = node, EXIT_SUCCESS);
}

static int	split_env_entry(char *env_entry, char **var_name, char **var_value)
{
	char	*env_copy;
	char	*equal;

	*var_value = NULL;
	env_copy = ft_strdup(env_entry);
	if (!env_copy)
		return (EXIT_FAILURE);
	equal = ft_strchr(env_copy, '=');
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
	int		result;

	i = 0;
	shell->env_list = NULL;
	while (env[i])
	{
		result = split_env_entry(env[i], &var_name, &var_value);
		if (result == EXIT_FAILURE)
		{
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		if (add_env_entry(shell, var_name, var_value) != EXIT_SUCCESS)
		{
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/* int	parse_env(t_shell *shell, char **env)
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
		env_copy = ft_strdup(env[i]);
		var_value = NULL;
		if (!env_copy)
		{
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		equal = ft_strchr(env_copy, '=');
		if (equal != NULL)
		{
			*equal = '\0';
			var_value = equal + 1;
		}	
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
} */
