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
			ft_putstr_nl("exit: not a valid identifier", STDERR_FILENO);
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
		ft_putstr_nl("exit: not a valid identifier", STDERR_FILENO);
		return (1);
	}
	return (0);
}
