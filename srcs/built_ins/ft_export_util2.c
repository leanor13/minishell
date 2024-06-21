/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/21 17:45:33 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_var_nosign_util(t_shell *shell, t_export info)
{
	if (info.sign == 0)
		add_back_env(&shell->env_list, info.args[info.i], NULL);
	return ;
}

int	add_var_nosign(t_shell *shell, t_export info)
{
	int		k;
	t_env	*env_lst_start;
	char	*var_name;

	info.sign = 0;
	var_name = NULL;
	info.name_len = ft_strlen(info.args[info.i]);
	var_name = ft_strndup(info.args[info.i], info.name_len);
	k = ft_strlen(var_name);
	env_lst_start = shell->env_list;
	while (shell->env_list)
	{
		if (!ft_strncmp(shell->env_list->var_name, var_name, k))
		{
			info.sign = 1;
			break ;
		}
		shell->env_list = shell->env_list->next;
	}
	shell->env_list = env_lst_start;
	add_var_nosign_util(shell, info);
	if (var_name)
		free(var_name);
	return (info.sign);
}

int	no_variable(char *equal_sign, t_export info)
{
	char	*var_name_test;
	char	*var_name;

	var_name = NULL;
	info.name_len = info.equal_sign - info.args[info.i];
	var_name = ft_strndup(info.args[info.i], info.name_len);
	if (equal_sign)
	{
		var_name_test = ft_strdup(var_name);
		if (!is_valid_varname(var_name_test))
		{
			ft_putstr_nl("export: not a valid identifier", STDERR_FILENO);
			free(var_name);
			free(var_name_test);
			return (1);
		}
		free(var_name_test);
	}
	if (var_name)
		free(var_name);
	return (0);
}

int	no_variable_novalue(char *var_name)
{
	if (!is_valid_varname(var_name))
	{
		ft_putstr_nl("export: not a valid identifier", STDERR_FILENO);
		return (1);
	}
	return (0);
}
