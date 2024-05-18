/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/17 22:46:18 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO
// add "" for var_value
// don't print = if no var_value

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


// void add_or_update_env_var(t_env **env_lst, const char *name, const char *value) 
// {
//     t_env *existing_var = find_env_var(*env_lst, name);

//     if (existing_var) {
//         free(existing_var->var_value);
//         existing_var->var_value = strdup(value);
//     } else {
//         t_env *new_var = malloc(sizeof(t_env));
//         new_var->var_name = strdup(name);
//         new_var->var_value = strdup(value);
//         new_var->next = *env_lst;
//         *env_lst = new_var;
//     }
// }

int	ft_export(t_shell *shell, t_arg *command)// do not change the struc
{
	int		i = 1;
	//char	*equal;
	//char	*var_name;
	//char	*var_value;
	//char 	**env = shell->env_2d;
	char 	**args = command->arguments; //here is the args
	t_env	*env_lst = shell->env_list;

	if (args[i] == NULL)
	{
		while (env_lst)
		{
			if (!env_lst->var_value)
				// TODO: this is not working - check why
				ft_printf("declare -x %s\n", env_lst->var_name);
			else if (ft_strcmp(env_lst->var_value, " ") == 0)
				ft_printf("declare -x %s=\"\"\n", env_lst->var_name);
			else
			{
				ft_printf("declare -x %s=\"", env_lst->var_name);
				ft_printf("%s\"\n", env_lst->var_value);
			}
			env_lst = env_lst->next;
		}
		return (EXIT_SUCCESS);
	}
	// while (args[i] != NULL) 
	// {
    //     char *equal_sign = strchr(args[i], '=');
    //     if (equal_sign) 
	// 	{
    //         size_t name_len = equal_sign - args[i];
    //         char *var_name = strndup(args[i], name_len);
    //         char *var_value = strdup(equal_sign + 1);

    //         add_or_update_env_var(&env_lst, var_name, var_value);

    //         free(var_name);
    //         free(var_value);
    //     } 
	// 	else 
    //         add_or_update_env_var(&env_lst, args[i], "");
    //     i++;
    // }
    // shell->env_list = env_lst;
	// while (args[i] != NULL)//doublechar
	// {
	// 	//if() use variabl name
	// 	return (1);// fix this
	// 	//TINA you have to do this
	// }
	return (EXIT_SUCCESS);
}
