#include "minishell.h"

/* 
	cm: カーソル位置を移動させる
	dc: １文字削除
	ce: カーソル位置以降を行削除
	im: 挿入モード
	ei: 挿入モード解除
*/

void	init_termcap(t_mini *mini)
{
	mini->tc.env = getenv("TERM");
	if (mini->tc.env == NULL)
		mini->tc.env = strdup_safely("xterm-256color");
	tgetent(NULL, mini->tc.env);
	mini->tc.move = tgetstr("cm", NULL);
	mini->tc.flush_char = tgetstr("dc", NULL);
	mini->tc.flush_line = tgetstr("ce", NULL);
	mini->tc.insert = tgetstr("im", NULL);
	mini->tc.uninsert = tgetstr("ei", NULL);
}
