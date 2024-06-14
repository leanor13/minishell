/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 19:06:12 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


{
	char	*var_value;
	int		k;
	t_env	*env_lst_start;

	var_value = ft_strdup(equal_sign + 1);
	k = ft_strlen(var_name);
	env_lst_start = shell->env_list
	while(shell->env_list)
	{
		if(!ft_strncmp(shell->env_list->var_name, var_name, k))
		{
			ft_changenode(&shell->env_list, var_value);
			free(var_name);	
			free(var_value);
			sign = 1;
			break;
		}
		shell->env_list = shell->env_list->next;
	}
	shell->env_list = env_lst_start;
	if (sign == 0)
	{
		add_back_env(&shell->env_list, var_name, var_value);
		free(var_name);	
		free(var_value);
	}
}


{
	size_t	name_len;
	char *var_name;
	char *var_name_test;

	name_len = equal_sign - args[i];
	if (equal_sign)
	{
		name_len = equal_sign - args[i];
		var_name = ft_strndup(args[i], name_len);
		var_name_test = ft_strdup(var_name);
		if(!is_valid_varname(var_name_test))
		{
			ft_putstr_nl("exit: not a valid identifier", STDERR_FILENO);
			free(var_name);
			free(var_name_test);
			return(EXIT_FAILURE);
		}
		free(var_name_test);
	}
}