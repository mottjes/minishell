/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:55:05 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/28 13:23:08 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expansion_env_vars(t_data *shell)
{
	char	*str_mod;
	int		len;
	int		i;
	int		j;

	i = 0;
	while (shell->input && shell->input[i])
	{
		str_mod = NULL;
		len = 0;
		j = 0;
		if (shell->input[i] == '\'')
		{
			i++;
			while (shell->input[i] != '\'')
				i++;
			if (shell->input[i] == '\'')
				i++;
		}
		if (shell->input[i] == '$')
		{
			i++;
			while (shell->input[i + len] && shell->input[i + len] != ' ' && shell->input[i + len] != '\"')
				len++;
			while (shell->envp[j])
			{
				if (!ft_strncmp(&shell->input[i], shell->envp[j], len))
				{
					if (!ft_strncmp(shell->envp[j] + len, "=", 1))
					{
						str_mod = copy_env_var(shell->input, i - 1, shell->envp[j], len);
						if (!str_mod)
							malloc_fail(shell);
						free(shell->input);
						shell->input = str_mod;
					}
				}
				j++;
			}
			if (!str_mod)
			{
				str_mod = remove_env_var(shell->input, i, len);
				if (!str_mod)
					malloc_fail(shell);
				free(shell->input);
				shell->input = str_mod;
			}
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
}
