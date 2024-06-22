/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/21 17:44:34 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_varname(const char *var_name)
{
	if (!ft_isalpha(*var_name) && *var_name != '_')
		return (0);
	while (*var_name)
	{
		if (!ft_isalnum(*var_name) && *var_name != '_')
			return (0);
		var_name++;
	}
	return (1);
}

void	ft_changenode(t_env **env_list, char *copy_value)
{
	free((*env_list)->var_value);
	(*env_list)->var_value = NULL;
	(*env_list)->var_value = ft_strdup(copy_value);
}

int	no_export(t_shell *shell, char **args)
{
	t_env	*env_lst_start;

	env_lst_start = shell->env_list;
	if (args[1] != NULL)
		return (0);
	if (args[1] == NULL)
	{
		while (shell->env_list)
		{
			if (!shell->env_list->var_value)
				ft_printf("declare -x %s\n", shell->env_list->var_name);
			else if (ft_strcmp(shell->env_list->var_value, " ") == 0)
				ft_printf("declare -x %s=\"\"\n", shell->env_list->var_name);
			else
			{
				ft_printf("declare -x %s=\"", shell->env_list->var_name);
				ft_printf("%s\"\n", shell->env_list->var_value);
			}
			shell->env_list = shell->env_list->next;
		}
		shell->env_list = env_lst_start;
	}
	return (1);
}

int	ft_export(t_shell *shell, t_arg *command)
{
	t_export	info;

	info.i = 1;
	info.args = command->arguments;
	if (no_export(shell, info.args))
		return (EXIT_SUCCESS);
	while (info.args[info.i] != NULL)
	{
		info.equal_sign = ft_strchr(info.args[info.i], '=');
		if (info.equal_sign)
		{
			if (no_variable(info.equal_sign, info))
				return (EXIT_SUCCESS);
			info.sign = add_var(shell, info);
		}
		else
		{
			if (no_variable_novalue(info.args[info.i]))
				return (EXIT_FAILURE);
			info.sign = (add_var_nosign(shell, info));
		}
		info.i++;
	}
	update_env_2d(shell);
	return (EXIT_SUCCESS);
}
