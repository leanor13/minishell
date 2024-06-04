/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/04 09:38:41 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("Signal SIGINT received, terminating process...\n");
        exit(EXIT_FAILURE);  // Or any cleanup code before exiting
    }
}

int main_parsing(t_shell *shell)
{
	char *command = NULL;
	t_arg *lst;
	//int saved_stdin = shell->std_fds[0];
	//int saved_stdout = shell->std_fds[1];
	//int saved_stderr = shell->std_fds[2];
	int	exit_status = EXIT_SUCCESS;

	lst = NULL;
	//signal(SIGINT, signal_handler);
	while (1)
	{
		//printf("saved_stdin: %d, STDIN:%d, shell->std_fds[0]: %d\n", saved_stdin, STDIN_FILENO, shell->std_fds[0]);
		if (dup2(shell->std_fds[0], STDIN_FILENO) == -1) // Reset STDIN_FILENO
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
		if (dup2(shell->std_fds[1], STDOUT_FILENO) == -1) // Reset STDIN_FILENO
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
		if (dup2(shell->std_fds[2], STDERR_FILENO) == -1) // Reset STDIN_FILENO
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
		if (shell->should_exit)
		{
			exit_status = shell->exit_status;
			free_shell(shell);
			exit(exit_status);
		}
		lst = NULL;
		command = NULL;
		/* Do we need something like ??
		if (isatty(STDIN_FILENO))
				command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
			else
			{
				char *line = get_next_line(STDIN_FILENO);
				if (line == NULL)
					end_of_input = true;
				command = ft_strtrim(line, "\n");
				free(line);
			}
		 */
		command = readline("\033[1;36mminishell\033[1;32m$\033[0;0m");
		if (command == NULL)
		{
			ft_putstr_nl("exit", STDERR_FILENO);
			free_shell(shell);
			exit(exit_status);
		}
		add_history(command);
		lst = ft_lexer(command, lst);
		/* t_arg *current = lst;
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
   		} */
		lst = ft_parser(lst, shell);
		shell->args_list = lst;
		if (shell->args_list != NULL)
			executor_main(shell);
		// while (shell->env_list) // TEST IF ENV_LIST GET DIFFERENTOUTSIDE OF THE FUNCITON
		// {
		// 	if (!shell->env_list->var_value)
		// 		ft_printf("out of function%s\n", shell->env_list->var_name);// TODO: this is not working - check why
		// 	else if (ft_strcmp(shell->env_list->var_value, " ") == 0)
		// 		ft_printf("out of function %s=\"\"\n", shell->env_list->var_name);
		// 	else
		// 	{
		// 		ft_printf("out of function %s=\"", shell->env_list->var_name);
		// 		ft_printf("%s\"\n", shell->env_list->var_value);
		// 	}
		// 	shell->env_list = shell->env_list->next;
		// }
		//update_env_2d(shell);
		//free_args(&lst);
		//free_command_list(&lst);
		free_args(&shell->args_list);
		free(command);
		close_all_protected(shell);

		// Reset STDIN_FILENO to the original terminal input after command processing
	}
	//ft_close(saved_stdin); // Close the saved STDIN_FILENO descriptor
	return (EXIT_SUCCESS);
}
