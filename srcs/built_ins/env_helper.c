/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:31:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/20 11:16:19 by yioffe           ###   ########.fr       */
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

int	convert_env_lst_to_2d(t_env *env_lst, char ***env_2d)
{
	char	*temp;
	int		i;

	if (setup_env_2d_array(env_lst, env_2d) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (env_lst)
	{
		if (!env_lst->var_name || !env_lst->var_value)
			(*env_2d)[i] = NULL;
		else
		{
			temp = ft_strjoin(env_lst->var_name, "=");
			if (protect_malloc(temp, env_2d) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			(*env_2d)[i] = ft_strjoin(temp, env_lst->var_value);
			free(temp);
			if (protect_malloc((*env_2d)[i], env_2d) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		i++;
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

