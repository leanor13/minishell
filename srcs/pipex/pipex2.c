int exec_pipe(t_shell *shell)
{
    int fd_pipe[2];
    int status = EXIT_SUCCESS;
    t_arg *current;
    int count;
    int i;
    t_arg *c_list = shell->args_list;
    int fd_in = 0;

    if (!c_list)
        return NEG_ERROR;

    current = c_list;
    count = args_count(c_list);

    while (current)
    {
        if (current->command)
        {
            // Set up input redirection if not specified
            if (!current->in_file && !shell->here_doc)
                current->fd_in = fd_in;

            // Set up output redirection if not specified
            if (current->next == NULL && !current->out_file)
                current->fd_out = STDOUT_FILENO;
            else if (!current->out_file)
                current->fd_out = fd_pipe[FD_OUT];

            // Debugging prints
            printf("current->command: %s\n", current->command);
            printf("command %s: fd_out: %d\n", current->command, current->fd_out);

            // Create pipe
            if (pipe(fd_pipe) == -1)
            {
                perror("Error creating pipe");
                return close_all_protected(), NEG_ERROR;
            }

            // Execute command
            if (exec_command(current, shell) < 0)
            {
                printf("closing fd_pipe[FD_OUT]: %d\n", fd_pipe[FD_OUT]);
                ft_close(fd_pipe[FD_OUT]);
                if (current->next != NULL)
                {
                    printf("closing fd_in: %d\n", fd_in);
                    ft_close(fd_in);
                }
                current = current->next;
                continue;
            }

            // Close write end of the pipe in the parent process
            printf("closing fd_pipe[FD_OUT]: %d\n", fd_pipe[FD_OUT]);
            ft_close(fd_pipe[FD_OUT]);

            // Set input for the next command
            fd_in = fd_pipe[FD_IN];
        }

        current = current->next;
    }

    // Close the last input file descriptor
    printf("closing fd_in: %d\n", fd_in);
    ft_close(fd_in);

    // Wait for child processes to finish
    for (i = 0; i < count; i++)
    {
        int child_status;
        waitpid(-1, &child_status, 0);
        if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != EXIT_SUCCESS)
            status = EXIT_FAILURE; // Update status if any child process failed
    }

    return status;
}
