/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:52:05 by frbeyer           #+#    #+#             */
/*   Updated: 2024/02/26 15:19:00 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_data t_data;
typedef	struct s_cmd t_cmd;

typedef struct s_exec
{
    char    *output;
}   t_exec;

void	executor(t_data *shell);


//          builtins
void	echo(t_data *shell, int i);
void	cd(t_data *shell, t_cmd *cmd);
void	env(char *envp[]);
void	pwd(t_data *shell);
void	ft_exit(t_data *shell);
void	unset(t_data *shell, char *var);
void	export(t_data *shell, char *var);

#endif
