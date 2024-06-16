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

int	add_var_nosign(char *var_name, t_shell *shell, int sign, int i, char **args)
{
	int		k;
	t_env	*env_lst_start;

	k = ft_strlen(var_name);
	env_lst_start = shell->env_list;
	while (shell->env_list)
	{
		if (!ft_strncmp(shell->env_list->var_name, var_name, k))
		{
			free(var_name);
			sign = 1;
			break ;
		}
		shell->env_list = shell->env_list->next;
	}
	shell->env_list = env_lst_start;
	if (sign == 0)
	{
		add_back_env(&shell->env_list, args[i], NULL);
		free(var_name);
	}
	return (sign);
}

void	add_var_free(int sign, char *var_value, t_shell *shell, char *var_name)
{
	if (sign == 0)
	{
		add_back_env(&shell->env_list, var_name, var_value);
		free(var_name);
		free(var_value);
	}
}

int	add_var(int sign, char *equal_sign, t_shell *shell, char *var_name)
{
	char	*var_value;
	int		k;
	t_env	*env_lst_start;

	if (equal_sign)
	{
		var_value = ft_strdup(equal_sign + 1);
		k = ft_strlen(var_name);
		env_lst_start = shell->env_list;
		while (shell->env_list)
		{
			if (!ft_strncmp(shell->env_list->var_name, var_name, k))
			{
				ft_changenode(&shell->env_list, var_value);
				free(var_name);
				free(var_value);
				sign = 1;
				break ;
			}
			shell->env_list = shell->env_list->next;
		}
		shell->env_list = env_lst_start;
		add_var_free(sign, var_value, shell, var_name);
	}
	return (sign);
}

int	no_variable(char *equal_sign, char *var_name)
{
	char	*var_name_test;

	if (equal_sign)
	{
		var_name_test = ft_strdup(var_name);
		if (!is_valid_varname(var_name_test))
		{
			ft_putstr_nl("exit: not a valid identifier", STDERR_FILENO);
			free(var_name);
			free(var_name_test);
			return (1);
		}
		free(var_name_test);
	}
	return (0);
}
