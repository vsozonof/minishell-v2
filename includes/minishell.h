/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:19 by tpotilli          #+#    #+#             */
/*   Updated: 2024/06/17 08:24:13 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <termcap.h>

# ifndef G_STATUS
#  define G_STATUS

extern int	g_status;

# endif

// ! ---------------------------------------------------------------------------
// ?							STRUCTURES DECLARATION
// ! ---------------------------------------------------------------------------

struct		s_parse;
struct		s_input;
struct		s_env;
struct		s_redirs;

typedef struct s_struct
{
	char			*name;
	char			*pid;
	char			*input;
	char			*user;
	char			*post;
	char			*w_d;
	char			**nv;
	struct s_parse	*data;
	struct s_env	*env;
	struct s_input	*inp;
	struct s_input	**multi_inp;
}	t_prompt;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
	int				ui;
}	t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			**param;
	char			**env;
	int				*tab;
	struct s_redirs	*redirs;
	struct s_cmd	*next;
	struct s_parse	*data;
}	t_cmd;

typedef struct s_input
{
	char			*str;
	char			**cmds;
	int				i;
	int				index;
	struct s_input	*next;
}	t_input;

typedef struct s_redirs
{
	int				type;
	int				fd;
	char			*file;
	struct s_redirs	*next;
}	t_redir;

typedef struct s_parse
{
	t_prompt		*pr;
	t_env			*env;
	t_input			*inp;
	t_input			**multi_inp;
	t_cmd			*exec;
	pid_t			*pid;
	int				**pipefd;
	char			*save_cmd;
	int				status_code;
	int				du1;
	int				du2;
	int				exited;
	char			*input;
	char			*head;
	char			*new_head;
	char			*tail;
	char			*to_add;
	char			**cmds;
	int				n_cmds;
	int				i_status;
	char			*c_status;
	int				**tab;
	char			**redir_tab;
	int				n_redirs;
	int				nb_redirs_ac;
	int				i;
	int				n;
	int				*here_doc_fd;
	int				index_here_doc;
	int				n_args;
	int				*cmd_valid;
	int				index_fd;
	int				index_redirs;
	int				nb_here_doc;
	char			*heredoc_fname;
}	t_data;

typedef struct s_lst_ch
{
	char			*whole_input;
	char			*cmds;
	int				*first;
	int				*last;
	int				*all_fd;
	struct s_lst_ch	*next;
}	t_cha;

typedef enum s_tokken
{
	OUTFILE,
	INFILE,
	LIMITER,
	APPEND
}	t_tokken;

typedef enum s_bultins
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET,
	NO,
}	t_bultins;

typedef struct s_exec
{
	int	tokken;
	int	result;
}	t_exec;

typedef struct s_pipex
{
	char	**path;
	char	*command;
	int		nbr_command;
	int		count_command;
	pid_t	childs;
	int		prev_pipes;
	int		infile;
	int		outfile;
	int		in;
	int		out;
	int		pipe[2];
	int		exit;
}	t_pipex;

// ! ---------------------------------------------------------------------------
// ?							INITIALIZATION
// ! ---------------------------------------------------------------------------

int				main(int argc, char **argv, char *envp[]);
int				get_input(t_prompt *prompt, t_data *data);
int				init_sbase(t_prompt *prompt, char **env);
int				init_extras(t_prompt *ptr);
int				init_str(t_data *data, t_prompt *prompt);
int				init_sig(t_prompt *prompt);
int				init_if_env(t_prompt *ptr, char **env);
int				init_if_no_env(t_prompt *ptr, char **envp);
int				put_env_to_lst(t_env *env, char **envp);
int				init_exec_var(t_data *data);
int				create_side_env(t_prompt *ptr);
t_input			*alloc_input_struct(void);
t_cmd			*alloc_node(t_cmd *pr);

// ! ---------------------------------------------------------------------------
// ?							INPUT PARSING
// ! ---------------------------------------------------------------------------

int				invalid_character_checker(int c, t_data *data);
int				is_input_valid(char *str, t_data *data);
int				is_piped_input_valid(char *str, t_data *data);
int				exception_checker(char *str, t_data *data);
int				exception_checker_2(char *str, int i, t_data *data);
int				unclosed_quote_detector(char *str, t_data *data);
int				expand_is_valid_char(int c);
int				is_valid_char(int c);

void			input_parser(t_prompt *prompt, t_data *data);
void			reg_expander(t_data *data, int i);
void			reg_expand_splitter(t_data *data, int i);
void			reg_expand_joiner(t_data *data);
void			tilde_expander(t_data *data, int i);
void			backslash_expander(t_data *data, int i);
void			search_and_split(t_data *data, int i);
void			quote_flagger(char *str, int i, int q_flag);

char			*quote_remover(t_data *data);
char			*quote_remover_v2(char *str);

// ! ---------------------------------------------------------------------------
// ?							PARSING UTILS
// ! ---------------------------------------------------------------------------

t_input			**alloc_struct(t_input **ptr, int n);
t_env			*ft_get_env_node(t_env *env, char *str);
int				alloc_multi_nodes(t_input **inp, t_cmd *pr);
void			multi_node_formatting(t_input **inp, t_data *data);
void			multi_format_node(t_cmd *pr, t_input *inp, t_data *data);
void			identify_nodes(t_input *p);
void			set_status(t_data *data, int status, char *str, char *cmd);
void			add_var_to_env(t_data *data, char *var);
void			del_var_from_env(t_data *data, char *var);

char			*input_splitter(t_data *data);
char			*extract_command_name(t_input *inp);
char			*get_tmp_filename(t_data *data);
char			**input_to_lst(t_data *data);
char			**pipes_splitter(char const *s, char c, t_data *data);
char			*ft_get_env(t_env *env, char *str);

int				multi_node_handler(t_data *data, int i);
int				alloc_redir_list(t_cmd *pr, int n);
int				format_node(t_cmd *pr, t_input *inp, t_data *data);
int				extract_params(t_input *inp, t_cmd *pr);
int				extract_redirs(t_input *inp, t_cmd *pr);
int				single_node_handler(t_data *data);
int				multi_input_to_lst(t_input **ptr, char ***tab, int i, int n);
int				expand_nodes(t_input *inp, t_data *data);
int				set_redir_type(char *token);
int				get_word_count(t_input *inp);
int				get_redir_count(t_input *inp);
int				get_n_redir(t_cmd *lst);
int				get_node_len(t_cmd *lst);
int				get_lst_len(t_input *lst);
int				get_heredoc_counter(t_cmd *node);
int				get_dtab_len(char **str);
int				heredoc_finder(t_cmd *node, t_data *data);
int				do_heredoc(char *delimiter, t_redir *redir_node, t_data *data);
int				do_heredoc_extra(char *delimiter, int fd);
int				put_input_to_lst(t_input *ptr, char **tab, t_data *data);
int				is_special_char(char c);
int				lexer_counter(char *str, int i, int c);
int				lexer_counter_helper(char *str, int i, int flag);
int				get_next_split(char *str, int i);
int				get_next_split_helper(char *str, int c, int flag);
int				token_identifier(char *str, int i);
int				node_identifier(char *str);
int				env_len(t_env *env);
int				is_there_pipe(t_prompt *prompt);
int				is_there_quotes(char *str);
int				is_there_tilde(char *str);
int				is_there_redirs(t_prompt *prompt);
int				ispipe(int c);
int				is_valid_pipe(char *str, t_data *data);
int				is_in_quotes(char *str, int c);
int				is_pipe_content_valid(char *str, t_data *data);
int				quote_skipper(char *str, int c);
int				syntax_error_finder(t_data *data, char *str);
int				wspace_after_redir_checker(t_data *data, char *str, int i);
int				token_after_redir_checker(t_data *data, char *str, int i);
int				redir_error_finder(t_data *data, char *str, int i);
int				format_node_extra(t_cmd *pr, t_input *inp, t_data *data, int n);

// ! ---------------------------------------------------------------------------
// ?							SIGNAL HANDLER
// ! ---------------------------------------------------------------------------

void			handle_signals(int signum);

// ! ---------------------------------------------------------------------------
// ?							Utils Free
// ! ---------------------------------------------------------------------------

void			free_master(t_data *data);
void			free_input_lst(t_input *lst);
void			free_cmd_nodes(t_cmd *nodes);
void			free_tri_table(char ***tab);
void			free_cmds(t_data *data);
void			free_env(t_env	*env);
void			free_env_tab(char **env);
void			free_end_of_program(t_prompt *p);
void			free_tab(int **tab);

// ! ---------------------------------------------------------------------------
// ?								Bultins
// ! ---------------------------------------------------------------------------

//cd .c 3/5
int				ft_cd(char **tab, t_env *env);
int				ft_cd_2(char *path, t_env *env);
void			ft_add_oldpwd(char *old, t_env *env);
int				ft_home(t_env *env);
void			ft_add_pwd(char *pwd, t_env *env);

//echo 2/5
int				ft_echo(char **tab);
void			ft_echo2(char **tab, int i, int n);

//env.c 1/5
int				ft_print_env(t_env *env);

//exit.c 5/5
long long int	ft_atoll_1(const char *str);
int				status_checker(char	*status, t_data *data);
void			execute_exit(char **param, t_data *data);

//export.c 5/5
int				ft_export(char **tab, t_env **env);
void			ft_export2(char *tab, t_env *tmp, t_env **env);
int				ft_find_plus(char *str);
int				ft_find_equal(char *str);
t_env			*ft_add_export(char *str, t_env **env);

//export2.c 3/5
int				ft_size_tab(char **tab);
int				ft_check_export(char *str);
void			ft_join_export(char *str, t_env *tmp);

//pwd.c 1/5
int				ft_pwd(void);

//unset.c 3/5
int				ft_unset(t_env **env, char **tab);
int				ft_unset_cmp(char *s1, char *s2);
void			ft_unset_remove(t_env	*tmp, t_env **env);

// ! ---------------------------------------------------------------------------
// ?								Exec
// ! ---------------------------------------------------------------------------

//exec_one.c 5/5
int				ft_exec_one(t_cmd *cmd, t_env **env, t_pipex *pip,
					t_data **data);
int				ft_execve_one(t_env **env, t_pipex *pip, t_cmd *tmp,
					t_data **data);
void			ft_free_pip(t_pipex *pip);

//exec_one2.c 1/5
void			ft_execve_one2(t_pipex *pip, t_cmd *tmp, t_data **data);

//exec_pipe.c 5/5
int				ft_exec_pipe(t_cmd *tmp, t_env **env, t_pipex *pip,
					t_data **data);
void			ft_exec_pipe2(t_pipex *pip);
void			ft_exec_pipe4(t_pipex *pip);
void			ft_exec_pipe4bis(t_pipex *pip);
void			ft_exec_pipe3(t_pipex *pip);

//exec_pipe2.c 3/5
void			ft_exec_pipe5(t_pipex *pip, t_env **env, t_cmd *tmp,
					t_data **data);
int				ft_exec_pipebultins(t_cmd *tmp, t_env **env, int tokken,
					t_data **data);
void			ft_close_one(int out, int in);

//exec0.c 2/5
int				ft_exec_all(t_cmd *cmd, t_env **env, t_pipex *pip,
					t_data **data);
void			ft_exec_all0(t_redir **redir, t_pipex **pip);

//exec.c 5/5
int				ft_exec(t_cmd **cmd, t_env **env, t_data **data);
void			ft_exec_all2(t_pipex *pip, t_redir **redir);
int				ft_wait_lstchild(t_pipex *pip);
int				ft_close_pipe(int count, int *pipe, int nbr_command,
					t_pipex *pip);
int				ft_close_fd_use(t_cmd *cmd);

//exec2.c 5/5
int				ft_create_pipe(int count, int *pipes);
int				ft_nbr_cmd(t_cmd *cmd);
void			ft_close_fd(int in, int out);
int				ft_check2(char *s);

//exev_pars.c 5/5
void			ft_path(t_env **env, t_pipex *pip);
char			*ft_command(t_pipex *pip, char *command, t_env **env,
					t_data **data);
int				ft_is_a_slash(char	*command);
void			ft_path2(t_pipex *pip);
char			*ft_join(char *first, char *second);

//exec_ft_command.c 4/5
char			*ft_command2(t_pipex *pip, char *command, t_env **env, int i);
void			ft_free_path(t_pipex *pip);
char			*ft_check_command(int fd, char *command, t_data **data);

//exec_utils.c 1/5
int				ft_exec_openfd(t_cmd **cmd, t_redir **tmp, t_pipex **pip);
int				ft_exec_bultins(t_cmd *cmd, t_env **env, int tokken,
					t_data **data);

/*----------------------------------------------------------------------------*/
/*                                    UTILS                                   */
/*----------------------------------------------------------------------------*/

//env_utils.c 5/5
int				ft_env_size(t_env *env);
t_env			*ft_get_env_pos(t_env *env, char *find);
t_env			*ft_get_env_pos_export(t_env *env, char *find);

//list_utils_2.c 3/5
t_env			*ft_lstlast_env(t_env *lst);
void			ft_lstadd_back_env(t_env **alst, t_env *new);

//utils_bultins.c 1/5
char			*ft_find_env(t_env *env, char *find);

//utils.c
void			ft_free_envp(char **envp);
char			*ft_strcat(char *s1, char *s2);
int				ft_strcmp(char *s1, char *s2);
#endif