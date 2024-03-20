/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:15:02 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 15:45:42 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	search_path(t_data *shell, t_cmd *cmds)
{
	char	**env_paths;
	char	*cmd_mod;
	char	*cmd_path;
	int		i;

	i = 0;
	while (shell->envp[i] && ft_strncmp(shell->envp[i], "PATH=", 5))
		i++;
	if (!shell->envp[i])
		return ;
	env_paths = ft_split(shell->envp[i] + 5, ':');
	cmd_mod = ft_strjoin("/", cmds->cmd);
	if (!cmd_mod || !env_paths)
		malloc_fail(shell);
	i = 0;
	while (env_paths[i])
	{
		cmd_path = ft_strjoin(env_paths[i], cmd_mod);
		if (!cmd_path)
			malloc_fail(shell);
		if (!access(cmd_path, F_OK))
		{
			cmds->path = cmd_path;
			break ;
		}
		i++;
	}
}

static void	print_error_2(t_data *shell, t_cmd *cmd, int error_nbr)
{
	if (error_nbr == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exit_status = 127;
		shell->restart = true;
		return ;
	}
	if (error_nbr == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		shell->exit_status = 126;
		shell->restart = true;
		return ;
	}
}

bool	check_path_given(t_data *shell, t_cmd *cmd)
{
	struct stat	filestat;

	if (cmd->cmd[0] == '/' || (cmd->cmd[0] == '.' && cmd->cmd[1] == '/'))
	{
		cmd->path = ft_strdup(cmd->cmd);
		if (!cmd->path)
			malloc_fail(shell);
		if (access(cmd->path, F_OK))
			return (print_error_2(shell, cmd, 1), true);
		else
		{
			if (stat(cmd->path, &filestat) == 0)
			{
				if (S_ISDIR(filestat.st_mode))
					return (print_error_2(shell, cmd, 2), true);
			}
		}
	}
	return (false);
}

int	cmds_count(t_token *token)
{
	int	count;

	count = 1;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

int	arg_count(t_token *token)
{
	int	count;

	count = 1;
	while (token && token->type == WORD)
	{
		while (token->type == RE_IN || token->type == RE_OUT
			|| token->type == RE_APP || token->type == HERE_DOC)
		{
			token = token->next;
			token = token->next;
		}
		token = token->next;
		count++;
	}
	return (count);
}
