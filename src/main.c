/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:42 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/04 17:39:15 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_num;

static void	checks_and_execution(t_sh *msh, char *temp)
{
	char	*input;

	input = syntax_check(msh, temp);
	if (msh->error == false)
	{
		lexer(input, msh);
		msh->exit_code = execution_branch(msh);
		free_lex(msh->lex_arr);
		msh->lex_arr = NULL;
	}
	close_all_hd_fd(msh);
	free(input);
	msh->error = false;
}

void	get_input(t_sh *msh)
{
	char	*temp;

	while (1)
	{
		receive_signal(0);
		temp = tcsetreadline(msh, 0);
		if (g_num == SIGINT)
		{
			msh->exit_code = 1;
			g_num = 0;
		}
		if (!temp)
		{
			free(temp);
			ft_exit(msh, NULL);
		}
		if (temp)
			add_history(temp);
		if (temp[0] != '\0')
			checks_and_execution(msh, temp);
	}
}

int	main(int ac, char **av, char **ev)
{
	t_sh	*msh;

	if (ac != 1)
	{
		ft_printf(2, "Invalid arg amount\n");
		exit(1);
	}
	msh = init_msh(ev);
	msh->lex_arr = NULL;
	load_termios(msh);
	get_input(msh);
	return (0);
}
