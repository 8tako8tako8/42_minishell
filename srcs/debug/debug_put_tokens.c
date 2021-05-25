#include "minishell.h"

void	put_tokens(t_token *token)
{
	while (token)
	{
		printf("====================\n");

		printf(" type : ");
		if (token->type == END)
			printf("END\n");
		if (token->type == PIPE)
			printf("PIPE\n");
		if (token->type == CMD)
			printf("CMD\n");
		
		printf(" str  : %s\n", token->str);
		
		token = token->next;
	}
}

