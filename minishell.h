/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:34:27 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/13 18:32:52 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <string.h>

enum				e_type
{
	COMMAND = 1,
	OPTION,
	RED_APP,
	RED_OUT,
	RED_IN,
	RED_HER,
	LIMITER,
	FILE_IN,
	FILE_OUT,
	FILE_APP,
	PIPE,
	VARIABLE,
};

typedef struct s_envi
{
	char			*variable;
	char			*value;
	int				print;
	char			*equal;
	struct s_envi	*next;
}					t_envir;

typedef struct s_stack
{
	char			*word;
	int				key;
	struct s_stack	*next;
}				t_stack;

// global struct ----------------------------------
typedef struct g_variables
{
	int			exit_flags;
	int			exit_stat;
	int			shlvl;
	int			path_fl;
	int			red_flag;
	int			delim_flags;
	int			herd_flags;
	int			r_falg;
	int			j_falg;
	int			c_falg;
	int			i_splt_falg;
	int			herdo_c;
	int			size;
	int			qts_flgs;
	int			prev_pipe_read;
	char		**envire;
	long long	n;
}					t_var;

typedef struct s_last
{
	char			**word;
	int				input;
	int				output;
	struct s_last	*next;
}					t_last;

// ---------------------------------UTILS FUNCT-------------------------------//
//util/utils1.c
void				ft_check_exit_st(void);
int					ft_strlen(const char *str);
long long			ft_atoll(char *str);
int					ft_strlen_no_null(const char *str);
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, int start, int len);
//util/utils2.c
char				*ft_strdup(const char *s1);
int					ft_isalpha(int c);
//util/utils3.c
int					ft_strcmp(char *s1, char *s2);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_isdigit(int c);
//util/utils4.c
void				ft_last_check(char *line);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
int					ft_atoi(const char *str);
int					is_numeric(const char *str);
void				free_tab(char **tab);
int					ft_strcmp(char *s1, char *s2);
char				*ft_itoa(unsigned int n);
//util/free_fnc.c
void				free_tab(char **str);
// ---------------------------------PRINC FUNCT-------------------------------//
//parsing/first_check.c
int					ft_first_check(char *str);
int					check_space(char *str);
//parsing/check_utils.c
int					check_character(char c, char *check);
//lexical/lexical_func.c
char				**merg_and_split_multiple_time_1(char *line);
int					cheking_(t_stack *tmp);
void				ft_remove_gv(char *str);
int					option_len(t_stack *list);
void				return_space_to_real_value(char *word);
char				*ft_add_variables(char *line, t_envir *envr, int f);
void				ft_option(t_stack *list, t_last *str);
void				lexical_function(char *line, t_envir **envr);
char				**ft_split_opera(char *s, char h);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_stack				*ft_my_lstnew(char *content, int key);
t_last				*ft_new_last_list(void);
t_envir				*creat_env_list(void);
char				**ft_merge_envr(t_envir *env);
void				ft_check_delim(char *str);
int					ft_herdoc(t_stack *list, t_envir *envr);
void				fd_herdoc(int fd[2]);
void				ft_herd(int sig);
char				*dell_qots(char *line);
int					ft_strlen_nospace(const char *str);
int					check_any_redire(char *str, t_stack **wrd);
int					check_expo(char *str);
// ---------------------------------EXEC FUNCT-------------------------------//
//execution/unset.c
char				**remove_line_from_array(char **array, char *line);
int					check_arg_unset(char *arg);
char				**remove_unset(char **array, char *arg);
void				ft_unset(t_envir **env, char **cmd);
//execution/pwd.c
void				ft_pwd(void);
//execution/cd.c
void				put_pwd(char *arg, char *c);
void				ft_cd(char *arg, t_envir *env);
//execution/exit.c
void				ft_exit(char **str);
//execution/env.c
void				ft_env(t_envir *a, int i, char **cmd);
//execution/echo.c
int					ft_newline(char *arg);
void				ft_echo(t_last *last, char **str);
//execution/
void				ft_execution(t_last *last, t_envir **envr);
void				ft_export(t_envir **env, char **cmd);
char				*ft_strncpy(char *dest, char *src, unsigned int n);
//envir
t_envir				*ft_no_env(void);
t_envir				*sort_env(t_envir *env);
void				ft_env_ex(t_envir *a);
t_envir				*replace_variables(char **env, int i);
void				ft_sigint(int sig);
int					ft_checker(char *line);
void				close_pipe(int pipe_fds[2]);
int					create_herdoc_file(char **name);
char				*generate_unique_filename(void);
int					generate_random_number(void);
char				*merge_tab(char **str);
char				*find_value(char *str, t_envir *env);
char				*merge_str(char **str);
void				convert_special_chars(char *line);
char				**merg_and_split_multiple_time_2(char *line);
char				*dell_space(char *line);
t_stack				*split_in_list(char *str);
t_last				*ft_last_list_get_ready(t_stack *head, t_envir *envr);
int					open_fd_out(char *word, int key);
int					handle_herdoc(t_stack *tmp, t_envir *envr,
						t_last *last, int i);
void				handle_file_input(t_last *last, t_stack **tmp);
int					handle_file_output(t_stack *tmp, int key);
int					ft_check_for_herdoc(t_stack *tmp, t_envir *envr,
						t_last *last);
void				ft_free_last(t_last **env);
void				ft_free_stack(t_stack **env);
char				*split_for_lexical(char *line);
int					ft_check_quotes(char *str);
t_envir				*return_back_ptr(t_envir *env);
void				ft_swap_node(t_envir *list);
int					ft_strcasecmp(const char *s1, const char *s2);
t_envir				*sort_env(t_envir *env);
char				*ft_get_variable(char *str, int *i);
char				*ft_get_value(char *str);
int					variable_exists(t_envir *tmp, char *variable);
void				ft_pros_two(t_envir *tmp, char **cmd, int j, int i);
char				*ft_getfile_name(char **cammnd, t_envir *envr);
int					ft_check_for_ex(t_last *last, t_last *prv,
						t_envir **env);
int					ft_check_for_builting(t_last *last, t_envir *env);
void				ret_toreal_v(char **str);
void				free_add(t_envir *existing);
void				ft_rem_quo(t_last *last);
char				*dell_quots(char *line);
int					ft_lstlast_size(t_last *lst);
char				*getfile_name_helper(t_envir *envr);
int					ft_strchr_sla(char *s, int c);

t_var	g_flags;
#endif