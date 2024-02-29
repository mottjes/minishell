/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:55:05 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/29 16:02:31 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expansion_env_vars(t_data *shell)
{
	char	*str_mod;
	int		len;
	int		i;

	i = 0;
	while (shell->input && shell->input[i])
	{
		len = 0;
		str_mod = NULL;
		i = skip_single_quotes(shell, i);
		if (shell->input[i] == '$' && shell->input[i + 1] != '?')
		{
			i++;
			while (shell->input[i + len] && shell->input[i + len] != ' '
				&& shell->input[i + len] != '\"')
				len++;
			str_mod = search_env_var(shell, i, len);
			if (!str_mod)
				str_mod = remove_env_var(shell, i, len);
			free(shell->input);
			shell->input = str_mod;
		}
		else
			i++;
	}
}

void	expansion_before_redirections(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->input && shell->input[i])
	{
		if ((shell->input[i] == '<' && shell->input[i + 1] != '<')
			|| (shell->input[i] == '>' && shell->input[i + 1] != '>'))
		{
			if (check_before_operator(shell, i))
				i++;
		}
		else if ((shell->input[i] == '<' && shell->input[i + 1] == '<')
			|| (shell->input[i] == '>' && shell->input[i + 1] == '>'))
		{
			if (check_before_operator(shell, i))
				i++;
			i++;
		}
		i++;
	}
}

void	expansion_after_redirections(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->input && shell->input[i])
	{
		if ((shell->input[i] == '<' && shell->input[i + 1] != '<')
			|| (shell->input[i] == '>' && shell->input[i + 1] != '>'))
		{
			if (check_after_operator(shell, i))
				i++;
		}
		else if ((shell->input[i] == '<' && shell->input[i + 1] == '<')
			|| (shell->input[i] == '>' && shell->input[i + 1] == '>'))
		{
			if (check_after_operator(shell, i + 1))
				i++;
			i++;
		}
		i++;
	}
}

void	expansion_pipes(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == '|')
		{
			if (check_before_operator(shell, i))
				i++;
			if (check_after_operator(shell, i))
				i++;
		}
		i++;
	}
}

void	expander(t_data *shell)
{
	if (shell->restart)
		return ;
	expansion_pipes(shell);
	expansion_before_redirections(shell);
	expansion_after_redirections(shell);
	expansion_env_vars(shell);
	expansion_exit_status(shell);
}
