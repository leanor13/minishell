/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/02 11:02:03 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// YULIA: let's check that varname is valid by using this function
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

void ft_changenode(t_env **env_list, char * copy_value)
{
	free((*env_list)->var_value);
	(*env_list)->var_value = NULL;
	(*env_list)->var_value = strdup(copy_value);
}

int	ft_export(t_shell *shell, t_arg *command)
{
	int		i = 1;
	char 	**args = command->arguments;
	t_env	*env_lst_start = shell->env_list;
	char *equal_sign = NULL;
	int	sign = 0;
	if (args[i] == NULL)
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
		return (EXIT_SUCCESS);
	}
	if (*args[i] == '0' || *args[i] == '1' || *args[i] == '2' || *args[i] == '3' || *args[i] == '4' \
			|| *args[i] == '5' || *args[i] == '6' || *args[i] == '7' || *args[i] == '8' || *args[i] == '9' \
			|| *args[i] == '-' || *args[i] == '+' || *args[i] == '!' || *args[i] == '?' || *args[i] == '$' \
			|| *args[i] == '=' || *args[i] == 34 || *args[i] == 39)
			// || shell->args_list->type == WRONG)
	{
		ft_printf("not a valid identifier\n");
		return(EXIT_FAILURE);
	}
	if (shell && shell->args_list && shell->args_list->type && shell->args_list->type == WRONG)
	{
		ft_printf("not a valid identifier\n");
		return(EXIT_FAILURE);
	}
	while (args[i] != NULL) 
	{
        equal_sign = strchr(args[i], '=');
        if (equal_sign)
		{
			size_t name_len = equal_sign - args[i];
			char *var_name = strndup(args[i], name_len);
			char *var_value = strdup(equal_sign + 1);
			int k = ft_strlen(var_name);
			t_env *env_lst_start = shell->env_list;
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
		else
		{
			if(*args[i] == '0' || *args[i] == '1' || *args[i] == '2' || *args[i] == '3' || *args[i] == '4' \
			|| *args[i] == '5' || *args[i] == '6' || *args[i] == '7' || *args[i] == '8' || *args[i] == '9' \
			|| *args[i] == '-' || *args[i] == '+' || *args[i] == '!' || *args[i] == '?' || *args[i] == '$' \
			|| *args[i] == '=' || *args[i] == 34 || *args[i] == 39 )
			//|| shell->args_list->type == WRONG)
			{
				ft_printf("not a valid identifier\n");
				return(EXIT_FAILURE);
			}
			if (shell && shell->args_list && shell->args_list->type && shell->args_list->type == WRONG)
			{
				ft_printf("not a valid identifier\n");
				return(EXIT_FAILURE);
			}
			add_back_env(&shell->env_list, args[i], NULL);
		}
        i++;
	}
	if (equal_sign)
		shell->env_list = env_lst_start;
	update_env_2d(shell);
	return (EXIT_SUCCESS);
}
