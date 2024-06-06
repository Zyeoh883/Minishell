/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:58:12 by sting             #+#    #+#             */
/*   Updated: 2024/06/05 13:08:44 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_or_add_variable(t_var *var_lst, char **cmd_arg, int index,
		int equal_index)
{
	char	*var_name;
	t_var	*node;

	var_name = ft_substr(cmd_arg[index], 0, equal_index);
	if_null_perror_n_exit(var_name, "ft_substr", EXIT_FAILURE);
	node = get_var_node(var_name, var_lst);
	if (node != NULL) // if variable exist
	{
		node->is_exported = true;
		if (cmd_arg[index][equal_index] == '=')
			set_var_value(var_name, &cmd_arg[index][equal_index + 1], var_lst);
	}
	else // if var don't exist
		var_lstadd_back(&var_lst, var_lstnew(cmd_arg[index], true));
	free(var_name);
}

int	execute_export(char **cmd_arg, t_var *var_lst)
{
	int	i;
	int	equal_index;

	printf(">>>>>BUILT_IN>>>>>\n");
	if (cmd_arg[1] == NULL)
		return (print_env_var(var_lst, "declare -x "));
	i = 0;
	while (cmd_arg[++i] != NULL)
	{
		equal_index = count_chars_until_equal_sign(cmd_arg[i]);
		if (is_var_name_valid(cmd_arg[i]) == EXIT_FAILURE)
			return (print_custom_err_n_return("export: `", cmd_arg[i],
					"\': not a valid identifier", EXIT_FAILURE));
		update_or_add_variable(var_lst, cmd_arg, i, equal_index);
	}
	return (EXIT_SUCCESS);
}