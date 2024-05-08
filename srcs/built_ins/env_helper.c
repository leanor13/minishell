/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:31:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/08 10:52:04 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_len_count(t_env *env_lst)
{
	int i;

	i = 0;
	while (env_lst != NULL)
	{
		i ++;
		env_lst = env_lst->next;
	}
	return (i);
}

int convert_env_lst_to_2d(t_env *env_lst, char ***env_2d)
{
	char	*temp;
	int		i;

	i = 0;
	free_string_array(env_2d);
	*env_2d = ft_calloc((env_len_count(env_lst) + 1), sizeof(char *));
	while (env_lst)
	{
		temp = ft_strjoin(env_lst->var_name, "=");
		if (!temp)
		{
			free_string_array(env_2d);
			return (perror("malloc error"), EXIT_FAILURE);
		}
		(*env_2d)[i] = ft_strjoin(temp, env_lst->var_value);
		if (!**env_2d )
		{
			free_string_array(env_2d);
			return (perror("malloc error"), EXIT_FAILURE);
		}
		i ++;
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
