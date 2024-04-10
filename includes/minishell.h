/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:19 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/28 06:37:59 by tpotilli         ###   ########.fr       */
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

// ! ---------------------------------------------------------------------------
// ?							INITIALIZATION
// ! ---------------------------------------------------------------------------

int		main(int argc, char **argv, char *envp[]);
int		get_input(t_prompt *prompt, t_data *data);
int		init_sbase(t_prompt *prompt, char **env);
int		init_extras(t_prompt *ptr);
int		init_str(t_data *data, t_prompt *prompt);
int		init_sig(t_prompt *prompt);
int		init_if_env(t_prompt *ptr, char **env);
int		init_if_no_env(t_prompt *ptr, char **envp);
int		put_env_to_lst(t_env *env, char **envp);
int		init_exec_var(t_data *data);
int		create_side_env(t_prompt *ptr);
t_input	*alloc_input_struct(void);
t_cmd	*alloc_node(t_cmd *pr);

// ! ---------------------------------------------------------------------------
// ?							INPUT PARSING
// ! ---------------------------------------------------------------------------

int		invalid_character_checker(int c, t_data *data);
int		is_input_valid(char *str, t_data *data);
int		is_piped_input_valid(char *str, t_data *data);
int		exception_checker(char *str, t_data *data);
int		exception_checker_2(char *str, int i, t_data *data);
int		unclosed_quote_detector(char *str, t_data *data);
int		expand_is_valid_char(int c);
int		is_valid_char(int c);

void	input_parser(t_prompt *prompt, t_data *data);
void	reg_expander(t_data *data, int i);
void	reg_expand_splitter(t_data *data, int i);
void	reg_expand_joiner(t_data *data);
void	tilde_expander(t_data *data, int i);
void	backslash_expander(t_data *data, int i);
void	search_and_split(t_data *data, int i);
void	quote_flagger(char *str, int i, int q_flag);

char	*quote_remover(t_data *data);
char	*quote_remover_v2(char *str);

// ! ---------------------------------------------------------------------------
// ?							PARSING UTILS
// ! ---------------------------------------------------------------------------

t_input	**alloc_struct(t_input **ptr, int n);
t_env	*ft_get_env_node(t_env *env, char *str);
int		alloc_multi_nodes(t_input **inp, t_cmd *pr);
void	multi_node_formatting(t_input **inp, t_data *data);
void	multi_format_node(t_cmd *pr, t_input *inp, t_data *data);
void	identify_nodes(t_input *p);
void	set_status(t_data *data, int status, char *str, char *cmd);
void	add_var_to_env(t_data *data, char *var);
void	del_var_from_env(t_data *data, char *var);

char	*input_splitter(t_data *data);
char	*extract_command_name(t_input *inp);
char	*get_tmp_filename(t_data *data);
char	**input_to_lst(t_data *data);
char	**pipes_splitter(char const *s, char c, t_data *data);
char	*ft_get_env(t_env *env, char *str);

int		multi_node_handler(t_data *data, int i);
int		alloc_redir_list(t_cmd *pr, int n);
int		format_node(t_cmd *pr, t_input *inp, t_data *data);
int		extract_params(t_input *inp, t_cmd *pr);
int		extract_redirs(t_input *inp, t_cmd *pr);
int		single_node_handler(t_data *data);
int		multi_input_to_lst(t_input **ptr, char ***tab, int i, int n);
int		expand_nodes(t_input *inp, t_data *data);
int		set_redir_type(char *token);
int		get_word_count(t_input *inp);
int		get_redir_count(t_input *inp);
int		get_n_redir(t_cmd *lst);
int		get_node_len(t_cmd *lst);
int		get_lst_len(t_input *lst);
int		get_heredoc_counter(t_cmd *node);
int		get_dtab_len(char **str);
int		heredoc_finder(t_cmd *node, t_data *data);
int		do_heredoc(char *delimiter, t_redir *redir_node, t_data *data);
int		do_heredoc_extra(char *delimiter, int fd);
int		put_input_to_lst(t_input *ptr, char **tab, t_data *data);
int		is_special_char(char c);
int		lexer_counter(char *str, int i, int c);
int		lexer_counter_helper(char *str, int i, int flag);
int		get_next_split(char *str, int i);
int		get_next_split_helper(char *str, int c, int flag);
int		token_identifier(char *str, int i);
int		node_identifier(char *str);
int		env_len(t_env *env);
int		is_there_pipe(t_prompt *prompt);
int		is_there_quotes(char *str);
int		is_there_tilde(char *str);
int		is_there_redirs(t_prompt *prompt);
int		ispipe(int c);
int		is_valid_pipe(char *str, t_data *data);
int		is_in_quotes(char *str, int c);
int		is_pipe_content_valid(char *str, t_data *data);
int		quote_skipper(char *str, int c);
int		syntax_error_finder(t_data *data, char *str);
int		wspace_after_redir_checker(t_data *data, char *str, int i);
int		token_after_redir_checker(t_data *data, char *str, int i);
int		redir_error_finder(t_data *data, char *str, int i);
int		format_node_extra(t_cmd *pr, t_input *inp, t_data *data, int n);

// ! ---------------------------------------------------------------------------
// ?							SIGNAL HANDLER
// ! ---------------------------------------------------------------------------

void	handle_signals(int signum);

// ! ---------------------------------------------------------------------------
// ?							Command
// ! ---------------------------------------------------------------------------

int		command_manager(t_data *data);
int		builtin_checker(char *tmp);
void	builtin_manager(t_data *data, int token, t_cmd *cmd);
int		pipex_exec(t_data *data);
int		ft_pipex(t_data *data);
char	*ft_pipex_helper(t_data *data, int i, int *file);
int		ft_pipex_helper_dup(t_data *data, int i);
int		child_process(t_data *data, t_cmd *cmd, int *file);
int		**parent_process(t_data *data, int i);
int		child_process_in_or_out(t_data *data, int i, int token);
int		child_process_middle(t_data *data, int token, int verif);
char	*ft_do_process(char *envp[], char *cmd, t_data *data);
char	*ft_do_process_helper(char *cmd, t_data *data);
int		ft_do_process_checker(char *cmd, t_data *data);
int		child_process_in(t_data *data, int i);
int		child_process_helper(t_data *data, t_cmd *cmd, int *file);
int		get_and_print_statuscode(t_data *data, int status);
int		builtin_multi(t_cmd *cmd, t_data *data, int *file);
int		check_dup(int pipe, int token, int pipe2);
char	**ft_get_path(char **env);
char	*ft_strjoin_help(char **path, char *cmd, int i);
void	free_pipe_begin(t_data *data, int token);
char	*do_process_2(char **path, char *buf2, char *cmd, t_data *data);
void	child_process_helper2(t_cmd *cmd, t_data *data, int *file);

// ! ---------------------------------------------------------------------------
// ?							Single_Pipe
// ! ---------------------------------------------------------------------------

int		*single_arg(t_data *data);
int		exec_single(t_data *data, char *comd, t_cmd *cmd, int *file);
int		builtin_single(t_cmd *cmd, t_data *data, int *file);
int		child_process_single(t_data *data, t_cmd *cmd, int *file, char *comd);

// ! ---------------------------------------------------------------------------
// ?							Redirection
// ! ---------------------------------------------------------------------------

int		*redirection_create(t_cmd *cmd, t_data *data, int *file_tab);
int		create_file(t_redir *nav, int file, t_data *data);
int		other_type_redir(t_redir *nav, int file, t_data *data);
int		redirection_dup1_in(int file);
int		redirection_dup1_out(int file);
int		*creating_file(t_redir *nav, t_data *data, t_cmd *cmd);
void	redir_here(t_data *data, int *file);

// ! ---------------------------------------------------------------------------
// ?							Free && utils Exec
// ! ---------------------------------------------------------------------------

int		wait_and_free(t_data *data);
int		get_kind_redirs_ac(char *input);
void	close_all_pipe(int **pipefd, t_data *data);
long	len_list(t_redir *redir);
void	free_all_pipe(int **pipefd);
void	free_all_fd(t_data *data, int i);
void	close_all_open_redirs(int *file, t_cmd *cmd);
void	free_problem(t_data *data, int *file, t_cmd *cmd);
void	redir_failed(t_data *data, int *file, int i);
void	free_problem_cmd_not_found(t_data *data, int *file, t_cmd *cmd);
void	close_open_redirs(int *file, int i);
long	len_cmd(t_cmd *cmd);
void	free_problem_single(t_data *data, int *file);
int		ft_create_fd(char *argv, int flag);
int		**alloc_pipe(void);
void	unlink_here_doc(t_data *data);

// ! ---------------------------------------------------------------------------
// ?							  Builtins
// ! ---------------------------------------------------------------------------

char	*export_extract_arg(char *str);
char	*extract_var_name(char *str, int i);
char	*extract_var_value(char *str, int i);
char	*unset_extract_var_name(char *args, int i);

int		export_valid_args_counter(char *str);
int		export_is_valid_arg(char *str, int i);
int		export_var_name_checker(char *str);
int		is_valid_var_first_char(int c);
int		is_valid_var_char(int c);
int		is_valid_var_name(char *var);
int		unset_var_name_skipper(char *args, int i);

void	echo_printer(char *param);
void	execute_cd(char **param, t_data *data);
void	change_directory(t_data *data, char *path);
void	go_back_one_level(t_data *data);
void	update_vars(t_data *data);
void	error_handling(int err, char *str, t_data *data);
void	execute_echo(char **param, t_data *data);
void	execute_pwd(t_data *data);
void	execute_env(t_data *data);
void	execute_export(char **param, t_data *data);
void	export_no_args(t_env *env);
void	export_error_handler(char *str, char *to_check, char *rest);
void	export_finalizer(char *args, int i, t_data *data);
void	do_export(char *var_name, char *var_value, t_data *data);
void	execute_unset(t_data *data);
void	do_unset(char *args, t_data *data);
void	execute_exit(char **param, t_data *data);

// ! ---------------------------------------------------------------------------
// ?							Utils Free
// ! ---------------------------------------------------------------------------

void	free_master(t_data *data);
void	free_input_lst(t_input *lst);
void	free_cmd_nodes(t_cmd *nodes);
void	free_tri_table(char ***tab);
void	free_cmds(t_data *data);
void	free_env(t_env	*env);
void	free_env_tab(char **env);
void	free_end_of_program(t_prompt *p);
void	free_tab(int **tab);

#endif