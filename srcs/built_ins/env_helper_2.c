/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:55:54 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/23 10:54:03 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*env_find_var(t_env *env_lst, char *var_name)
{
	if (!env_lst)
		return (NULL);
	while (env_lst)
	{
		if (ft_strcmp(env_lst->var_name, var_name) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

int	arr_len(char **arr)
{
	int	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len ++;
	return (len);
}

int	save_2d_env(char **arr, char ***dest)
{
	int	i;

	i = 0;
	if (!arr)
	{
		*dest = ft_calloc(1, sizeof(char *));
		if (!*dest)
			return (ft_putstr_nl("malloc failure", STDERR_FILENO),
				EXIT_FAILURE);
		**dest = NULL;
		return (EXIT_SUCCESS);
	}
	*dest = ft_calloc((arr_len(arr) + 1), sizeof(char *));
	if (!*dest)
		return (ft_putstr_nl("malloc failure", STDERR_FILENO), EXIT_FAILURE);
	while (arr[i])
	{
		(*dest)[i] = ft_strdup(arr[i]);
		if (!(*dest)[i])
			return (free_string_array(dest), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
