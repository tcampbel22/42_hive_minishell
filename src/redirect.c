/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:48:01 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/28 11:57:34 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	r_input(t_lex **lex_arr)
{
	int	infile;

	infile = open(lex_arr[1], O_RDONLY, 0444);
	if (infile == -1)
		error_exit();
	if (dup2(infile, STDIN_FILENO) == -1)
		error_exit("", 127);

}
