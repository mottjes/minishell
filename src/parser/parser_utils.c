/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mika <mika@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:15:02 by mottjes           #+#    #+#             */
/*   Updated: 2024/09/26 20:04:39 by mika             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_env_paths(t_data *s, t_cmd *c, char ***env_paths, char **cmd_mod)
{
	int	i;
	int	j;

	i = 0;
	while (s->envp[i] && ft_strncmp(s->envp[i], "PATH=", 5))
		i++;
	if (!s->envp[i])
		return ;
	*env_paths = ft_split(s->envp[i] + 5, ':');
	if (!env_paths)
		malloc_fail(s);
	*cmd_mod = ft_strjoin("/", c->cmd);
	if (!cmd_mod)
	{
		j = 0;
		while (env_paths[j])
			free(env_paths[j++]);
		free(env_paths);
		malloc_fail(s);
	}
}

void	search_path(t_data *shell, t_cmd *cmds, int i)
{
	char	**env_paths;
	char	*cmd_mod;
	char	*cmd_path;

	get_env_paths(shell, cmds, &env_paths, &cmd_mod);
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
		free(cmd_path);
		i++;
	}
	i = 0;
	while (env_paths[i])
		free(env_paths[i++]);
	free(env_paths);
	free(cmd_mod);
}

void	print_error_2(t_data *shell, t_cmd *cmd, int error_nbr)
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
