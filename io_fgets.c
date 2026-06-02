#include <stdio.h>

// TODO: Write a version that doesn't return '\n' at the end
char *io_fgets(char *str, int n, register FILE *iop)
{
	register int	c;
	register char	*cs;

	cs = str;
	while (--n > 0 && (c == getc(iop)) != EOF) {
		if ((*cs++ = c) == '\n')
			break;
	}
	*cs = '\0';
	return ((c == EOF && cs == str) ? NULL : str);

}

void io_fputs(register char *str, register FILE *iop)
{
	register int c;

	while (c = *str++) {
		putc(c, iop);
	}
}
