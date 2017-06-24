#include "./common.h"

const char* USAGE = "Usage:\n\
  pid -n <number-of-pids>\n\
";

void
fork_so_much(int n)
{
	int pid;

	printf("Starting to spawn %d blocking children\n", n);
	while (--n) {
		switch (pid = fork()) {
			case -1:
				_must(0, "Fork returned -1.");
				break;
			case 0:
				printf("[%d] - blocking\n", n);
				wait_until_signalized();
				return;
		}
	}
}

int
main(int argc, char** argv)
{
	args_t args = { 0 };

	parse_args(argc, argv, &args);
	fork_so_much(args.n);
	wait_until_signalized();

	return 0;
}