/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:37:46 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/10 10:21:52 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execution(t_last *last, char **env, t_envir *envr)
{
	int		prev_pipe_read;
	char	**envire;
	t_last	*prv;
	int		size;
	int		pipe_fds[2];
	pid_t	pid;
	char	*path;
	int		output_fd;
	int		input_fd;

	prev_pipe_read = STDIN_FILENO;
	ft_rem_quo(last);
	prv = NULL;
	envire = env;
	size = ft_lstlast_size(last);
	while (last)
	{
		ret_toreal_v(last->word);
		if (!ft_check_for_ex(last, prv, envr, size))
			last = last->next;
		else
		{
			envire = ft_merge_envr(envr);
			if (last->next)
			{
				if (pipe(pipe_fds) == -1)
				{
					perror("pipe");
					exit(0);
				}
			}
			pid = fork();
			if (pid == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				signal(SIGINT, SIG_DFL);
				if (prev_pipe_read != STDIN_FILENO)
				{
					if (dup2(prev_pipe_read, STDIN_FILENO) == -1)
					{
						perror("dup2");
						exit(0);
					}
					close(prev_pipe_read);
				}
				if (last->next)
				{
					if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
					{
						perror("dup2");
						exit(0);
					}
					close(pipe_fds[1]);
				}
				close_pipe(pipe_fds);
				if (last && last->output != -1)
				{
					output_fd = last->output;
					if (dup2(output_fd, STDOUT_FILENO) == -1)
					{
						perror("dup2");
						exit(0);
					}
				}
				if (last && last->input != -1)
				{
					input_fd = last->input;
					if (dup2(input_fd, STDIN_FILENO) == -1)
					{
						perror("dup2");
						exit(0);
					}
				}
				if (ft_check_for_builting(last, envr))
				{
					exit(0);
				}
				else
				{
					path = ft_getfile_name(last->word, envr);
					if (!path)
					{
						last->output = 2;
						ft_putstr_fd(ft_strjoin(ft_strjoin(ft_strdup("minishell: command not found: "), last->word[0]), "\n"), last->output);
						exit(127);
					}
					execve(path, last->word, envire);
					perror("minishell");
					exit(0);
				}
			}
			else if (pid < 0)
			{
				perror("fork");
				exit(0);
			}
			else
			{
				if (prev_pipe_read != STDIN_FILENO)
					close(prev_pipe_read);
				if (last->next)
					close(pipe_fds[1]);
				prev_pipe_read = pipe_fds[0];
				prv = last;
				last = last->next;
			}
			free_tab(envire);
		}
	}
	while (wait(&g_flags.exit_stat) > 0)
		;
}
