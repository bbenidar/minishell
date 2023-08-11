/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:24:13 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/11 21:34:23 by bbenidar         ###   ########.fr       */
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
	if (last && last->input != -1)
		if (dup2(last->input, STDIN_FILENO) == -1)
			return (perror("dup2"), exit(0));
}

void	ft_execution_helper(t_last **last,
		t_envir **envr, int pipe_fds[2])
{
	char	*path;

	execute_child_helper(*last, pipe_fds);
	if (ft_check_for_builting((*last), *envr))
		exit(0);
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
		perror("misadasdasnishell");
		exit(0);
	}
}

void	process_exi(t_last **last, t_last **prv,
		t_envir **envr, int pipe_fds[2])
{
	pid_t	pid;

	if ((*last)->next)
		if (pipe(pipe_fds) == -1) 
			return (perror("pipe"), exit(0));
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		ft_execution_helper(&(*last), envr, pipe_fds);
	else if (pid < 0)
		return (perror("fork"));
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
}

void	ft_execution(t_last *last, t_envir **envr)
{
	t_last	*prv;
	int		pipe_fds[2];
	int		size;

	prv = NULL;
	g_flags.prev_pipe_read = STDIN_FILENO;
	ft_rem_quo(last);
	g_flags.envire = NULL;
	size = ft_lstlast_size(last);
	while (last)
	{
		ret_toreal_v(last->word);
		if (!ft_check_for_ex(last, prv, envr, size))
			last = last->next;
		else
		{
			g_flags.envire = ft_merge_envr(*envr);
			process_exi(&last, &prv, envr, pipe_fds);
			free_tab(g_flags.envire);
		}
	}
	while (wait(&g_flags.exit_stat) > 0)
		;
}
