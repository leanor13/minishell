/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:30:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/30 12:53:32 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO check it with real minishell

// void	remove_arg(char **env, char *arg)
// {
// 	int		len_arg;
// 	char	**tmp;

// 	if (ft_getenv(env, arg) == NULL)
//         return ;
// 	len_arg = ft_strlen(arg);
// 	while (*env)
// 	{
// 		if (ft_strncmp(*env, arg, len_arg) == 0 && (*env)[len_arg] == '=')
// 		{
// 			tmp = env;
// 			while (*(tmp + 1) != NULL)
//             {
//                 *tmp = *(tmp + 1);
//                 tmp++;
//             }
//             *tmp = NULL;
//             return;
// 		}
// 		env ++;
// 	}
// }

// int	ft_unset(t_shell *shell, t_arg *command)// TINA it is related to export
// {
// 	char 	**env = shell->env_2d;
// 	char 	**args = command->arguments; 
	
// 	if (*env == NULL || *args == NULL || **args == '\0')
// 		return (EXIT_SUCCESS);// if malloc fails it is EXIT_FAILURE
// 	// while (*args != NULL)
// 	// {
// 	// 	remove_arg(env, *args);
// 	// 	args ++;
// 	// }
// 	return (EXIT_SUCCESS);
// }

// void	ft_delnode(t_env *env_list, int l)
// {
// 	t_env	**temp_prev = NULL;
// 	t_env	**temp_del = NULL;
// 	int		i;

//     // if (l == 1) 
// 	// {
// 	// 	*env_list = current->next;
// 	// 	free(current->var_name);
// 	// 	free(current->var_value);
// 	// 	free(current);
// 	// 	return;
//     // }
// 	i = 1;
// 	while(env_list && i < l)
// 	{
// 		*temp_prev = env_list;
// 		env_list = env_list->next;
// 	}
// 	env_list = env_list->next;
// 	*temp_del = env_list;
// 	(*temp_prev)->next = (*temp_del)->next->next;
// 	env_list->next = NULL;
// 	free(env_list->var_name);
// 	free(env_list->var_value);
// }

void ft_delnode(t_env **env_list, int l)
{
    t_env *temp_prev = NULL;
    t_env *temp_del = NULL;
    t_env *current = *env_list;
    int i;

	i = 0;
	if (l == 0)
	{
		temp_del = current;
		*env_list = current->next;
		free(temp_del->var_name);
		free(temp_del->var_value);
		free(temp_del);
		return;
	}
	while (i < l && current)
	{
		temp_prev = current;
		current = current->next;
		i++;
	}
	temp_del = current;
	
	//current->next = NULL;
	if (temp_prev != NULL)
		temp_prev->next = temp_del->next;
	temp_del->next = NULL;
	free(temp_del->var_name);
	free(temp_del->var_value);
	free(temp_del);
}

int	ft_unset(t_shell *shell, t_arg *command)// do not change the struc
{
	int		i = 1;
	int		l = 0;
	int		k = 0;
	//char	*equal;
	//char	*var_name;
	//char	*var_value;
	//char 	**env = shell->env_2d;
	char 	**args = command->arguments; //here is the args
	char	*find_command = NULL;
	t_env	*env_lst;

	if (args[i] == NULL)
		return (EXIT_SUCCESS);
	while(args[i])
	{
		l = 0;
		env_lst = shell->env_list;
		find_command = ft_strdup(args[i]);
		k = ft_strlen(find_command);
		while(shell->env_list)
		{
			if(!ft_strncmp(shell->env_list->var_name, find_command, k))
			{
				ft_delnode(&env_lst, l);
				break ;
			}
			l++;
			shell->env_list = shell->env_list->next;
		}
		free(find_command);
		i++;
	}
	shell->env_list = env_lst;
	
	//env_lst = shell->env_list;
	// while (env_lst) // FIRST TEST
	// {
	// 	ft_printf("%s=\"", env_lst->var_name);
	// 	ft_printf("%s\"\n", env_lst->var_value);
	// 	env_lst = env_lst->next;
	// }
	update_env_2d(shell);// I amd not sure if I need this it MAYBE DELETE LATER
	// char 	**env = shell->env_2d;// SECOND TEST
	// int 	fd_out = STDOUT_FILENO;

	// i = 0;
	// while (env && env[i] != NULL)
	// {
	// 	if (*env[i] != '\0' && *env[i] != '=' && ft_strchr(env[i], '='))
	// 		ft_putstr_nl(env[i], fd_out);
	// 	i ++;
	// }
	return (EXIT_SUCCESS);
}
