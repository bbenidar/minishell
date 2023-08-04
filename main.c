#include "minishell.h"

void ft(int i)
{
	if (i >= 16)
		ft(i / 16);
	write(1, &"0123456789abcdef"[i % 16], 1);
}


int main()
{
	// char *str = "\t, \x1b, \x11, \x00, \x16, \x0b, \x1d, \x19, \x17";
				//   9,  27,  17,   0,  22,  11,  29,  25,  23,
				//	 c   t    f     l    e    a    r    n    {
	write(1, "23 = ", 6);
	ft(23);
	puts("");
	write(1, "110 = ", 7);
	ft('{');
	puts("");
}