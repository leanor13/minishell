/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/15 19:06:24 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int main_parsing(t_shell *shell)
{
	char *command = NULL;
	t_arg *lst;
	int saved_stdin = shell->std_fds[0]; // Save the original STDIN_FILENO

	lst = NULL;
	while (1)
	{
		printf("saved_stdin: %d, STDIN:%d, shell->std_fds[0]: %d\n", saved_stdin, STDIN_FILENO, shell->std_fds[0]);
		if (dup2(saved_stdin, STDIN_FILENO) == -1) // Reset STDIN_FILENO
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
		lst = NULL;
		command = NULL;
		command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		if (command == NULL)
		{
			ft_putstr_nl("exit", STDERR_FILENO);
			exit(0);
		}
		add_history(command);
		lst = ft_lexer(command, lst);
		t_arg *current = lst;
		int	lst_num = 0;
   	 	while (current)
    	{	
		// printf("%sOUTPUT\n", current->out_file);
		// printf("%sHEREDOC\n", current->here_doc);
			lst_num++;
			printf("---NODE%i before parser---\n", lst_num);
        	printf(" %s,", current->str);
        	printf("type %i\n", current->type);
        	current = current->next;
   		}
		lst = ft_parser(lst);
		shell->args_list = lst;
		//printf("out_2: %s\n", shell->args_list->out_file[0]);
		//printf("out_1: %s\n", shell->args_list->out_file[1]);
		//printf("out_1: %s\n", shell->args_list->out_file[2]);
		if (shell->args_list != NULL)
			executor_main(shell);
		free_stackfinal(&lst);
		free(command);

		// Reset STDIN_FILENO to the original terminal input after command processing
	}
	ft_close(saved_stdin); // Close the saved STDIN_FILENO descriptor
	return (EXIT_SUCCESS);
}
