/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:24:13 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/14 11:31:57 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_child_helper(t_last *last, int pipe_fds[2])
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (g_flags.prev_pipe_read != STDIN_FILENO)
	{
		if (dup2(g_flags.prev_pipe_read, STDIN_FILENO) == -1)
			return (perror("dup2"), exit(0));
		close(g_flags.prev_pipe_read);
	}
	if (last->next)
	{
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), exit(0));
		close(pipe_fds[1]);
	}
	close_pipe(pipe_fds);
	if (last && last->output != -1)
		if (dup2(last->output, STDOUT_FILENO) == -1)
			return (perror("dup2"), exit(0));
	if (last && last->input != -1 && last->input != STDIN_FILENO)
		if (dup2(last->input, STDIN_FILENO) == -1)
			return (perror("dup2"), exit(0));
}

void	ft_execution_helper(t_last **last,
		t_envir **envr, int pipe_fds[2])
{
	char	*path;

	execute_child_helper(*last, pipe_fds);
	if (ft_check_for_builting((*last), *envr))
		exit(g_flags.exit_stat);
	else
	{
		path = ft_getfile_name((*last)->word, *envr);
		if (!path)
		{
			(*last)->output = 2;
			ft_putstr_fd(ft_strjoin(ft_strjoin(
						ft_strdup("minishell: command not found: "),
						(*last)->word[0]), "\n"), (*last)->output);
			exit(127);
		}
		execve(path, (*last)->word, g_flags.envire);
		perror("minishell");
		exit(127);
	}
}

int	process_exi(t_last **last, t_last **prv,
		t_envir **envr, int pipe_fds[2])
{
	pid_t	pid;

	if ((*last)->next)
		if (pipe(pipe_fds) == -1) 
			return (perror("pipe"), -1);
	pid = fork();
	if (pid == 0)
		ft_execution_helper(&(*last), envr, pipe_fds);
	else if (pid < 0)
		return (perror("fork"), -1);
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		if (g_flags.prev_pipe_read != STDIN_FILENO)
			close(g_flags.prev_pipe_read);
		if ((*last)->next)
			close(pipe_fds[1]);
		g_flags.prev_pipe_read = pipe_fds[0];
		*prv = (*last);
		(*last) = (*last)->next;
	}
	return (pid);
}

void	waiting_for_ex(pid_t pid)
{
	pid_t	wait_pid;
	int		exit_status;

	while (1)
	{
		wait_pid = wait(&exit_status);
		if (wait_pid <= 0)
			break ;
		if (wait_pid == pid)
			g_flags.exit_stat = exit_status;
	}
	if (WTERMSIG(g_flags.exit_stat) == SIGINT)
		g_flags.exit_stat = 130 * 256;
	if (WTERMSIG(g_flags.exit_stat) == SIGQUIT)
		g_flags.exit_stat = 131 * 256;
	signal(SIGINT, ft_sigint);
}

void	ft_execution(t_last *last, t_envir **envr)
{
	t_last	*prv;
	pid_t	pid;
	int		pipe_fds[2];

	prv = NULL;
	g_flags.prev_pipe_read = STDIN_FILENO;
	ft_rem_quo(last);
	g_flags.envire = NULL;
	g_flags.size = ft_lstlast_size(last);
	signal(SIGINT, SIG_IGN);
	while (last)
	{
		ret_toreal_v(last->word);
		if (g_flags.size <= 1 && !ft_check_for_ex(last, prv, envr))
			last = last->next;
		else
		{
			g_flags.envire = ft_merge_envr(*envr);
			pid = process_exi(&last, &prv, envr, pipe_fds);
			if (pid == -1)
				break ;
			free_tab(g_flags.envire);
		}
	}
	waiting_for_ex(pid);
}
