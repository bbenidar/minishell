/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:34:27 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/25 15:37:33 by bbenidar         ###   ########.fr       */
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

int exit_stat;

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
	struct s_envi	*next;
}					t_envir;

typedef struct s_stack
{
	char			*word;
	int				key;
	struct s_stack	*next;
}					t_stack;

typedef struct s_last
{
	char			**word;
	int				input;
	int				output;
	struct s_last	*next;
}					t_last;

// ---------------------------------UTILS FUNCT-------------------------------//
//util/utils1.c
int					ft_strlen(const char *str);
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
//util/utils4.c
int	ft_atoi(const char *str);
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
char				*ft_add_variables(char *line, t_envir *envr);
void				ft_option(t_stack *list, int i, t_last *str);
void				lexical_function(char *line, char **env, t_envir *envr);
char				**ft_split_opera(char const *s, char h);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_stack				*ft_my_lstnew(char *content, int key);
t_last				*ft_new_last_list(void);
t_envir				*creat_env_list(void);
char				**ft_merge_envr(t_envir *env);
// ---------------------------------EXEC FUNCT-------------------------------//
//execution/unset.c
char				**remove_line_from_array(char **array, char *line);
int					check_arg_unset(char *arg);
char				**remove_unset(char **array, char *arg);
void				ft_unset(t_envir *env, char *cmd);
//execution/pwd.c
void				ft_pwd(void);
//execution/cd.c
void				put_pwd(char *arg, char *c);
void				ft_cd(char *arg, t_envir *env);
//execution/exit.c
void				ft_exit(char **str);
//execution/env.c
void				ft_env(t_envir *a);
//execution/echo.c
int					ft_newline(char *arg);
void				ft_echo(t_last *last, char **str);
//execution/
void				ft_execution(t_last *last, char **env, t_envir *envr);
void				ft_export(t_envir *env, char **cmd);
#endif