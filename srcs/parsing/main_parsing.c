/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:42:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/30 15:47:14 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>


// #define	SIG_ERR	 ((__sighandler_t) -1)	/* Error return.  */
// #define	SIG_DFL	 ((__sighandler_t)  0)	/* Default action.  */
#define	SIG_IGN	 ((__sighandler_t)  1)	/* Ignore signal.  */
#define	SIGINT		2	/* Interactive attention signal.  */
#define	SIGTERM		15	/* Termination request.  */

#define	SIGQUIT		3//quit
#define	SIGKILL		9//kill is more like an action

volatile int exit_sig;

// void	handle_signal()
// {
// 	struct sigaction	sa;
// 	struct sigaction	act;

// 	sa.sa_flags = SA_RESTART;
// 	act.sa_flags = SA_RESTART;
// 	act.sa_handler = SIG_IGN;
// 	sigemptyset(&act.sa_mask);
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &act, NULL);
// 	sigaction(SIGTERM, &act, NULL);
// }
// {
// 	sigemptyset(&signal.sa_mask);
// 	sigaddset(&bitset, SIGUSR1);
// 	sigaddset(&bitset, SIGUSR2);
// 	signal.sa_handler = ft_signalhandler;
// 	signal.sa_flags = SA_SIGINFO; //SA_RESTART
// 	signal.sa_sigaction = ft_decodesignal;
// 	if (sigaction(SIGUSR1, &signal, NULL) == -1) 
// 	{
// 		ft_printf("Error: invalid signal setup");
// 		exit(1);
// 	}
// 	if (sigaction(SIGUSR2, &signal, NULL) == -1)
// 	{
// 		ft_printf("Error: invalid signal setup");
// 		exit(1);
// 	}
// }

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
	int saved_stdin = shell->std_fds[0]; // Save the original STDIN_FILENO
	int	exit_status = EXIT_SUCCESS;

	lst = NULL;
	signal(SIGINT, signal_handler);
	while (1)
	{
		//printf("saved_stdin: %d, STDIN:%d, shell->std_fds[0]: %d\n", saved_stdin, STDIN_FILENO, shell->std_fds[0]);
		if (dup2(saved_stdin, STDIN_FILENO) == -1) // Reset STDIN_FILENO
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
		//handle_signal();
		// if (exit_sig == 1)
		// 	shell->exit_status = 130;
		// if (exit_sig != 0)
		// 	g_sig = 0;
		if (command == NULL)
		{
			ft_putstr_nl("exit", STDERR_FILENO);
			free_shell(shell);
			exit(exit_status);
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
		free_stackfinal(&lst);
		free(command);
		close_all_protected(shell);

		// Reset STDIN_FILENO to the original terminal input after command processing
	}
	//ft_close(saved_stdin); // Close the saved STDIN_FILENO descriptor
	return (EXIT_SUCCESS);
}
