#ifdef NO_CURL

int main()
{
	return 125;
}

#else /* !NO_CURL */

#include "http.c"

#define url_normalize(u) http_options_url_normalize(u)

int main(int argc, char **argv)
{
	const char *usage = "test-url-normalize [-p | -l] <url1> | <url1> <url2>";
	char *url1, *url2;
	int opt_p = 0, opt_l = 0;

	/*
	 * For one url, succeed if url_normalize succeeds on it, fail otherwise.
	 * For two urls, succeed only if url_normalize succeeds on both and
	 * the results compare equal with strcmp.  If -p is given (one url only)
	 * and url_normalize succeeds, print the result followed by "\n".  If
	 * -l is given (one url only) and url_normalize succeeds, print the
	 * returned length in decimal followed by "\n".
	 */

	if (argc > 1 && !strcmp(argv[1], "-p")) {
		opt_p = 1;
		argc--;
		argv++;
	} else if (argc > 1 && !strcmp(argv[1], "-l")) {
		opt_l = 1;
		argc--;
		argv++;
	}

	if (argc < 2 || argc > 3)
		die(usage);

	if (argc == 2) {
		url1 = url_normalize(argv[1]);
		if (!url1)
			return 1;
		if (opt_p)
			printf("%s\n", url1);
		if (opt_l)
			printf("%u\n", (unsigned)strlen(url1));
		return 0;
	}

	if (opt_p || opt_l)
		die(usage);

	url1 = url_normalize(argv[1]);
	url2 = url_normalize(argv[2]);
	return (url1 && url2 && !strcmp(url1, url2)) ? 0 : 1;
}

#endif /* !NO_CURL */
