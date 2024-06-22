/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:11:30 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/21 19:32:43 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_string_array(char ***str_arr)
{
	int	i;

	if (!*str_arr)
		return ;
	i = 0;
	while ((*str_arr)[i])
	{
		free((*str_arr)[i]);
		(*str_arr)[i] = NULL;
		i++;
	}
	free(*str_arr);
	*str_arr = NULL;
}

void	free_env_lst(t_env *env_lst)
{
	t_env	*current;
	t_env	*prev;

	current = env_lst;
	if (!env_lst)
		return ;
	while (current)
	{
		prev = current;
		current = current->next;
		if (prev->var_name)
			free(prev->var_name);
		if (prev->var_value)
			free(prev->var_value);
		free(prev);
	}
}

void	ft_free(char **str)
{
	if (!str || !*str)
		return ;
	if (*str)
		free(*str);
	*str = NULL;
}

void	free_args(t_arg **args_list)
{
	t_arg	*curr_arg;
	t_arg	*next_arg;

	if (!args_list || !args_list[0])
		return ;
	curr_arg = *args_list;
	while (curr_arg)
	{
		next_arg = curr_arg->next;
		ft_free(&curr_arg->str);
		free_string_array(&curr_arg->arguments);
		free_string_array(&curr_arg->out_file);
		free_string_array(&curr_arg->in_file);
		free_string_array(&curr_arg->here_doc);
		curr_arg->command = NULL;
		curr_arg->built_in_fn = NULL;
		ft_free(&curr_arg->path);
		free(curr_arg);
		curr_arg = next_arg;
	}
	*args_list = NULL;
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free_string_array(&shell->env_2d);
	free_env_lst(shell->env_list);
	free_args(&shell->args_list);
	close_all_protected(shell);
	dup2(shell->std_fds[0], STDIN_FILENO);
	dup2(shell->std_fds[1], STDOUT_FILENO);
	dup2(shell->std_fds[2], STDERR_FILENO);
	ft_close(shell->std_fds[0]);
	ft_close(shell->std_fds[1]);
	ft_close(shell->std_fds[2]);
	return ;
}
