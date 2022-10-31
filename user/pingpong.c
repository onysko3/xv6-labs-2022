// cvicenie 1 uloha "pingpong"

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

    int to_child[2];
    int to_parent[2];

    pipe(to_child);
    pipe(to_parent);

    int pid = fork();

    if (pid == 0) {
        char received;
        int r = read(to_child[0], &received, 1);
        if (r == 1)
            printf("%d: received ping\n", getpid());
        write(to_parent[1], "y", 1);
    } else if (pid > 0) {
        write(to_child[1], "x", 1);
        char received;
        int r = read(to_parent[0], &received, 1);
        if (r == 1)
            printf("%d: received pong\n", getpid());
    } else {
        fprintf(2, "error creating process\n");
        exit(1);
    }

    exit(0);
}
