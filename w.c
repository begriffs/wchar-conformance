#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include <unicode/uchar.h>
#include <unicode/utf8.h>

/* max utf-8 code units needed for a codepoint */
#define MAX_UTF8_REP 4

int main(void)
{
	bool    conforming = true;
	char    utf8[1+MAX_UTF8_REP];
	wchar_t wide[1+MAX_UTF8_REP]; /* same width is more than enough */

	UChar32 c;
	size_t  written;

	if (!setlocale(LC_CTYPE, "en_US.UTF-8"))
	{
		fputs("Cannot set locale\n", stderr);
		return EXIT_FAILURE;
	}

#ifdef __STDC_ISO_10646__
	printf("__STDC_ISO_10646__ is %ld\n", __STDC_ISO_10646__);
#else
	puts("__STDC_ISO_10646__ is not defined");
#endif

	for (c = 0; c < 0xF0000; c++)
	{
		if (u_charType(c) != U_SURROGATE)
		{
			written = 0;
			U8_APPEND_UNSAFE(utf8, written, c);
			utf8[written] = '\0';

			mbstowcs(wide, utf8, MAX_UTF8_REP);
			if (wcslen(wide) > 1)
			{
				fprintf(stderr,
					"Not conforming: U+%lx expands to %zu wide characters\n",
					(unsigned long)c, wcslen(wide));
				conforming = false;
			}
			else if ((unsigned long)c != (unsigned long)wide[0])
			{
				fprintf(stderr,
					"Not conforming: U+%lx turned into wchar_t %lx\n",
					(unsigned long)c, (unsigned long)wide[0]);
				conforming = false;
			}
		}
	}
	if (conforming)
		puts("wchar_t encodes all codepoints correctly");

	return conforming ? EXIT_SUCCESS : EXIT_FAILURE;
}
