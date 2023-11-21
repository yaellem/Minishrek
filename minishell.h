/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:44:36 by mabed             #+#    #+#             */
/*   Updated: 2023/11/21 16:18:11 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "messages.h"
# include <dirent.h> //opendir readdir closedir
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h> //signal kill sigaction sigemptyset sigaddset
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h> //printf perror
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string.h>    //sterror
# include <sys/ioctl.h> //ioctl
# include <sys/stat.h>  //stat lstat fstat
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_PWD 2048
# define LL_MAXOU 9223372036854775807ULL
#define BUILTIN_RET -42
#define BUILTIN_ERR 1
#define NO_BUILTIN  -1
#define FALSE	1
#define TRUE 0
typedef struct s_data	t_data;

// extern int				g_status;
// extern	uint64_t			g_data_signal_exit[3];


typedef enum e_signals
{
	DEFAULT_SIG = 1,
	HEREDOC_SIG,
	CHILD_SIG,
	PARENT_SIG
}						t_signals;

typedef enum e_tokens
{
	SPACES,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	PIPE,
	ALPHANUMERIC,
	DOLLAR,
	INTERRO,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
	CMD,           //comande
	FILE_IN,       //word == '<'
	HERE_DOC,      // word == '<<'
	FILE_OUT,      //word == '>'
	FILE_OUT_SUR,  //word == '>>'
	OPEN_FILE,     // word following '<'
	LIMITOR,       // word following '<<'
	EXIT_FILE,     // word followinf '>'
	EXIT_FILE_RET, // word following '>>'
}						t_tokens;

typedef struct s_env
{
	char				*content;
	struct s_env		*next;
}						t_env;

typedef struct t_here
{
	char				*delim;
	int					pipe[2];
}						t_here;

typedef struct s_list
{
	char				*content;
	struct s_list		*next;
	struct s_list		*prev;
	t_data				*data;
	t_tokens			token;
	int					indice;
}						t_list;

typedef struct s_exec
{
	char				**path;
	pid_t				*pids;
	int					fd[2];
	int					prev;
	char				**cmds;
	char				*cmdpath;
	// int			nb_cmd;
	// char		*infile;
	// char		*outfile;
	// int			len;
	// char		*limiter;
	// int			fd_h;
	// int			here_doc;
	int					j;
}						t_exec;

typedef struct s_data
{
	t_list				*first;
	t_list				*last;
	int					exit_code;
	struct s_env		*env_list;
	char				**envi;
	char				***tb_cmd;
	t_exec				*exec;
	int					nb_cmd;
	int					nb_here;
	t_here				*here;
	int					n;
	int					here_status;
	int					cat;
	char				*readlin_return;
}						t_data;


void					free_list_env(t_env *env);
void					ft_negative(char *line);
int						verif_quote(char *line, t_data *data);
t_list					*ft_lstnew(t_data *data, char content, int i);
t_list					*ft_lstadd_back(t_list **lst, t_list *new);
void					creat_list(char *str, t_data *dbl_list);
char					*c_to_str(char c);
// void		tokens_distrib(t_list *list);
void					join_link(t_data *data);
t_tokens				get_token(char *str);
int						syntax_error(t_data *data);
int						verif_spaces_chevron(t_list *tmp);
int						verif_pipe(t_list *tmp);
t_env					*ft_envnew(char *content);
t_env					*ft_envadd_back(t_env **lst, t_env *new);
t_env					*creat_env_lst(char **content);
char					*get_path_var(t_env *env, char *str, int i);
void					replace_quote(t_data *data);
void					replace_dollar_quote(t_list *lst);
void					ft_positive(t_data *data);
int						var_env_len(char *str);
int						var_dollar_len(char *str);
char					*replace_alpha_null(t_list *lst, int i);
char					*replace_alpha_env(t_list *lst, char *str, int i);
void					del_link(t_list *lst);
// void		del_next_link(t_list *lst);
char					*replace_dollar_alpha(t_list *lst);
char					*replace_dollar_digit(t_list *lst);
char					*replace_dollar_return_code(t_list *lst);
void					replace_dollar(t_data *data);
char					*replace_dollar_alpha2(t_list *lst);
char					*replace_dollar_digit2(t_list *lst);
char					*replace_dollar_return_code2(t_list *lst);
char					*replace_alpha_env2(t_list *lst, char *str);
char					*replace_alpha_null2(t_list *lst);
void					free_list(t_list *lst);
void					free_data(t_data *data);
void					free_env(t_env *env);
char					**env2(t_env *env);
void					del_empty_join_quote(t_data *data);
int						verif_chev_next_chev(t_list *tmp);
t_list					*ft_lstnew2(t_data *data, char content, int i);
void					creat_list2(char *str, t_data *dbl_list, t_list **first,
							t_list **last);
t_tokens				get_token2(char *str);
void					join_link2(t_list **first, t_list **last);
void					integration(t_list **lst);
char					***tab_cmd(t_data *dbl_list);
int						nb_cmd(t_list *lst);
void					get_token3(t_list **list);
void					get_token4(t_list **list);
void					get_token5(t_list **list);
char					***sub_tab_cmd(t_list *user_input_first, char ***tab);
void					free_tab2(char ***tab);
void					free_tab(char ***tab);
void					ctrlc_child(int sig);
char					*get_path_var1(char **env);
char					**get_paths_from_environment(char *path);
void					free_tab1(char **tab);
char					*access_check(char **env, char *cmd);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2,
							const size_t n);
void					free_all_data(t_data *data, int code, int code2);
void					close_fd(int *fd);
void					close_pipes(t_data *data);
void					sub_redirect(t_data *data, int fd);
void					redirect(t_data *data);
void					child_process_2(t_data *data, char ***cmds, int i,
							t_list **tmp);
// void					child_process_2(t_data *data, char ***cmds, int i);
void					loop_cmd(t_data *data);
int						input_lexer(t_data *data);
void					exec_cmd(t_data *data);
int						ft_verif_built(char **cmds, t_data *data);
void					ft_verif_built2(char **cmds, t_data *data);
void					ft_verif_built3(char **cmds, t_data *data);
int						ft_printf_fd(int fd, const char *s, ...);
int						redirect2(t_data *data, t_list *tmp1);
int						open_file2(int fd, t_list *tmp, t_data *data);
int 					here_doc(t_data *data, char *str);
int						count_hd(t_list *list);
void					ft_getdelims(char *str, t_here *here, t_data *data);
void					child_hd(t_data *data, char *str);
char					*openfileshd(int index, t_here *here);
char					*get_word(char *str, t_list **tmp);
int						get_len_word(char *str);

/* *** cd.c *** */

int						cd_to_many(char **cmd);
int						cd_home(char **cmd, char **env, t_data *data);
int						cd_minus(char **cmd, char **env, t_data *data);
int						cd_point_point(t_data *data);
int						cd(char **cmd, t_data *data);
void					modif_env(t_data *data, char *new_pwd);
int						cd_home2(char **cmd, char **env, t_data *data);
int						cd_minus2(char **cmd, char **env, t_data *data);
int						cd_point_point2(t_data *data);
int						cd2(char **cmd, t_data *data);
int						ft_strlen_tab(char **tab);

/* *** echo.c *** */

void					parse_echo_option(char **echo, int *i, int *n);
void					echo(char **echo);

int						pwd(void);

/* *** env.c *** */

void					env_builtin(char **env);

/* *** export.c *** */

int						parse_export(char *new_export_var);
int						add_to_env(char ***env, char *cmd, t_env **envi);
// int						add_to_env(char **env, char *cmd, t_env **envi);
int						update_env(char ***env, char *cmd, t_env **envi);
// int						update_env(char **env, char *cmd, t_env **envi);
void					update_lst_env(char *cmd, t_env **env, char **var);
int						export(char **cmd, t_data *data);

/* *** export_noargs.c *** */

void					sort_index(char **tab, int *index, int size);
void					print_export(char **tab, int *index, int size);
void					export_noargs(char **env);
void					export2(char **cmd, t_data *data);
void					ft_swap(int *a, int *b);

/* *** unset.c *** */

t_env					*return_link_by_str(t_env *env, char *str);
t_env					*ft_lstnew_env(void *content);
int						pop_node(t_env **head, t_env *to_remove);
int						unset_end(char ***env, t_env *head);
int						unset(char **cmd, char ***env);

void					ft_lstdelone_env(t_env *lst, void (*del)(void *));
void					ft_lstclear_env(t_env **lst, void (*del)(void *));
void					ft_lstadd_back_env(t_env **lst, t_env *newl);
t_env					*ft_lstlast_env(t_env *lst);
int						ft_lstsize_env(t_env *lst);

/* *** utils.c *** */

t_env					*env_to_lst(char **env);
char					*ft_get_env(char *var_name, char **env);
char					**lst_to_chartab(t_env *env);
char					*trim_path(char *path);
char					**copy_tab(char **src);
void					init_environ(void);
void					update_env_lst(t_list **env, char *cmd);
t_data					*starton(void);

// *** exit_builtin.c ***

long long				ft_atoull_exit(char *str, int e);
int						exit_builtin(char **cmd, t_data *data, int e);

int						is_builtin(char **cmds);

/* *** sigaction_utils.c *** */

void					sigint_handler_default(int signum);
void					sig_handler_parent(int signum);
void					sig_handler_heredoc(int signum);

/* *** signals.c *** */

int						default_config(void);
int						heredoc_config(void);
int						child_config(void);
int						parent_config(void);
int						config_signals(int config);
void					antislash(int sig);
void					ctrlc(int sig);
void					ctrlc_2(int sig);

void					free_data(t_data *data);
void	free_data_in_parent(t_data *data);
// void		ft_positive(char *line);
// t_list		*ft_lstnew(char content, t_data *dbl_list);
// t_list		*ft_lstadd_back(t_list **lst, t_list *new);
// void		creat_list(char *str, t_data *dbl_list);
// char		*c_to_str(char c);
// void		tokens_distrib(t_list *list);
// void		join_link(t_list *list, t_data *data);
// t_tokens	get_token(char *str);
// int			ft_comp_env(t_list *list, char *str);
// void		ft_replace_dollar(t_list *list, char *str, int i);
// void		str_shift(t_list *list);
// void		ft_dollar(t_list *list);
// void		ft_double_quote(t_list *list);
// void		ft_simple_quote(t_list *list);
// int			check_quote(t_list *list);

#endif
