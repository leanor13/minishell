/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/16 16:13:35 by thuy-ngu         ###   ########.fr       */
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

int	no_export(t_shell *shell, char **args, t_env *env_lst_start )
{
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
	int		i;
	char	**args;
	char	*equal_sign;
	int		sign;
	t_env	*env_lst_start;
	char	*var_name;
	size_t	name_len;

	env_lst_start = shell->env_list;
	i = 1;
	args = command->arguments;
	equal_sign = NULL;
	sign = 0;
	if (no_export(shell, args, env_lst_start))
		return (EXIT_SUCCESS);
	while (args[i] != NULL) 
	{
		equal_sign = strchr(args[i], '=');
		if (equal_sign)
		{
			name_len = equal_sign - args[i];
			var_name = ft_strndup(args[i], name_len);
			if (no_variable(equal_sign, var_name))
				return (EXIT_SUCCESS);
			sign = add_var(sign, equal_sign, env_lst_start, shell, var_name);
		}
		else
		{
			if (!is_valid_varname(args[i]))
			{
				ft_putstr_nl("exit: not a valid identifier", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			name_len = ft_strlen(args[i]);
			var_name = ft_strndup(args[i], name_len);
			sign = (add_var_nosign(var_name, shell, sign, i, args));
		}
		i++;
	}
	if (equal_sign)
		shell->env_list = env_lst_start;
	update_env_2d(shell);
	return (EXIT_SUCCESS);
}
