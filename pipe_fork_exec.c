#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void usage (const char *prog) {
    printf ("Usages: %s [file_path]\n", prog);
        exit (1);
}

int main (int argc, char *argv[]) {
    // Check there is one and only one argument
    if (argc < 1 || argc > 2) {
        usage (argv[0]);
    }

	int pp[2];

	if (pipe(pp) == -1){
		exit(1);
	}

	switch (fork()) {
		case -1:
			exit(1);
			break;
		case 0:
			close(0);
			dup(pp[0]);
			close(pp[0]);
			close(pp[1]);
			char *args[] = {"hash_words", NULL};
			execv(args[0], args);
			break;
		default:
			close(1);
			dup(pp[1]);
			close(pp[0]);
			close(pp[1]);
			execv("split_words", argv);
			break;
	}
    
    exit (0);
}