/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:15:16 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/19 15:23:56 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	expansion_env_vars(t_data *shell)
{
	int		i;

	i = 0;
	while (shell->input[i])
	{
		i = skip_single_quotes(shell, i);
		if (shell->input[i] == '$')
		{
			if (shell->input[i + 1] == ' ' || shell->input[i + 1] == '\"')
				i++;
		}
		if (shell->input[i] == '$' && shell->input[i + 1] != '?'
			&& shell->input[i + 1] != ' ' && shell->input[i + 1])
		{
			i++;
			expansion_env_var(shell, i);
		}
		else if (shell->input[i])
			i++;
	}
}

static void	expansion_exit_status(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == '\'')
		{
			i++;
			while (shell->input[i] && shell->input[i] != '\'')
				i++;
			if (shell->input[i] == '\'')
				i++;
		}
		if (shell->input[i] == '$' && shell->input[i + 1] == '?')
			add_exit_status(shell, i);
		if (shell->input[i])
			i++;
	}
}

static void	expansion_redirections(t_data *shell)
{
	expansion_before_redirections(shell);
	expansion_after_redirections(shell);
}

static void	expansion_pipes(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->input[i])
	{
		i = skip_quotes(shell->input, i);
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
	expansion_pipes(shell);
	expansion_redirections(shell);
	expansion_env_vars(shell);
	expansion_exit_status(shell);
}
