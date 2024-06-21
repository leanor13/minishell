/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/16 16:30:17 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_var_free(int sign, char *var_value, t_shell *shell, char *var_name)
{
	if (sign == 0)
	{
		add_back_env(&shell->env_list, var_name, var_value);
		free(var_value);
	}
}

int	add_var(t_shell *shell, t_export info)
{
	char	*var_value;
	int		k;
	t_env	*env_lst_start;
	char	*var_name;

	info.sign = 0;
	var_name = NULL;
	info.name_len = info.equal_sign - info.args[info.i];
	var_name = ft_strndup(info.args[info.i], info.name_len);
	if (info.equal_sign)
	{
		var_value = ft_strdup(info.equal_sign + 1);
		k = ft_strlen(var_name);
		env_lst_start = shell->env_list;
		while (shell->env_list)
		{
			if (!ft_strncmp(shell->env_list->var_name, var_name, k))
			{
				ft_changenode(&shell->env_list, var_value);
				free(var_value);
				info.sign = 1;
				break ;
			}
			shell->env_list = shell->env_list->next;
		}
		shell->env_list = env_lst_start;
		add_var_free(info.sign, var_value, shell, var_name);
	}
	free(var_name);
	return (info.sign);
}
