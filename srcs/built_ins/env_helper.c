/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:31:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/07 15:20:27 by yioffe           ###   ########.fr       */
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
