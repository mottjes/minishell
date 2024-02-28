/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:33:53 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/28 13:21:43 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*copy_env_var(char *old_str, int i, char *envp, int len_var)
{
	char	*new_str;
	int		len_envp;
	int		len;

	len_envp = ft_strlen(envp + len_var + 1);
	len = i;
	len += len_envp;
	len += ft_strlen(old_str + i + len_var);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, old_str, i + 1);
	ft_strlcpy(new_str + i, envp + len_var + 1, len_envp + 1);
	ft_strlcpy(new_str + i + len_envp, old_str + i + len_var + 1, len - i - len_envp + 1);
	return (new_str);
}

char	*remove_env_var(char *old_str, int i, int len_var)
{
	char	*new_str;
	int		len;

	len = ft_strlen(old_str) - len_var;
	new_str = malloc(sizeof(char) * (len));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, old_str, i);
	ft_strlcpy(new_str + i - 1, old_str + i + len_var, len - i + 1);
	return (new_str);
}

void	add_space(t_data *shell, int i)
{
	int		size;
	char	*new_input;

	size = ft_strlen(shell->input) + 2;
	new_input = malloc(sizeof(char) * size);
	if (!new_input)
		malloc_fail(shell);
	ft_strlcpy(new_input, shell->input, i + 1);
	new_input[i] = ' ';
	ft_strlcpy(new_input + i + 1, shell->input + i, size - i);
	free(shell->input);
	shell->input = new_input;
}

int	check_before_operator(t_data *shell, int i)
{
	if (!shell->input)
		return (0);
	if (shell->input[i - 1] && shell->input[i - 1] != ' ')
	{
		add_space(shell, i);
		return (1);
	}
	return (0);
}

int	check_after_operator(t_data *shell, int i)
{
	if (!shell->input)
		return (0);
	if (shell->input[i + 1] && shell->input[i + 1] != ' ')
	{
		add_space(shell, i + 1);
		return (1);
	}
	return (0);
}
