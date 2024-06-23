/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/23 16:12:21 by yioffe           ###   ########.fr       */
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
	t_env	*env_lst_start;
	char	*name;

	info.sign = 0;
	info.name_len = info.equal_sign - info.args[info.i];
	name = ft_strndup(info.args[info.i], info.name_len);
	if (!name)
		return (0);
	if (info.equal_sign)
	{
		var_value = ft_strdup(info.equal_sign + 1);
		if (!var_value)
			return (0);
		env_lst_start = shell->env_list;
		while (shell->env_list)
		{
			if (!ft_strncmp(shell->env_list->var_name, name, ft_strlen(name)))
			{
				ft_changenode(&shell->env_list, var_value);
				free(var_value);
				info.sign = 1;
				break ;
			}
			shell->env_list = shell->env_list->next;
		}
		shell->env_list = env_lst_start;
		add_var_free(info.sign, var_value, shell, name);
	}
	return (free(name), info.sign);
}

int	update_env_2d(t_shell *shell)
{
	if (convert_env_lst_to_2d(shell->env_list, &shell->env_2d) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
