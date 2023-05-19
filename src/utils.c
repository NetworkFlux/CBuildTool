#include "c_builder.h"

void	err_n_die(const char *msg, ...)
{
	int		errSave;
	va_list	ap;

	// Any system or library call can set errno, so save it
	errSave = errno;

	// Print the message to std OUT
	va_start(ap, msg);
	vfprintf(stdout, msg, ap);	// vfprintf = variadic fprintf
	fprintf(stdout, "\n");
	fflush(stdout);				// Flush std OUT

	// If errno was set, print the error message
	if (errSave != 0)
	{
		fprintf(stdout, "(errno = %d) : %s\n", errSave, strerror(errSave));
		fprintf(stdout, "\n");
		fflush(stdout);
	}
	va_end(ap);

	exit(EXIT_FAILURE);
}