/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:35:48 by frbeyer           #+#    #+#             */
/*   Updated: 2024/02/23 20:32:39 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_data t_data;
typedef	struct s_cmd t_cmd;
typedef struct s_exec t_exec;

void	echo(t_data *shell, int i);
void	cd(t_data *shell, t_cmd *cmd);
void	env(char *envp[]);
void	pwd(t_data *shell);
void	ft_exit(t_data *shell);

#endif