/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:55:54 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/18 16:30:59 by thuy-ngu         ###   ########.fr       */
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
		// else
		// 	return(NULL);
		env_lst = env_lst->next;
	}
	return (NULL);
}
