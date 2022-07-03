#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void c_action(int sig) {}

int main(int argc, char** argv) {
    int h, d;

    if (argc >= 3) {
        h = atoi(argv[1]);
        d = atoi(argv[2]);
    } else {
        printf("Podaj wysokosc drzewa i liczbe dzieci:\n");
        exit(0);
    }

    fflush(stdout);

    pid_t child_pid;
    // Aktualna glebokosc w drzewie.
    int j = 0;

    struct sigaction cact;
    cact.sa_flags = 0;
    cact.sa_handler = c_action;
    sigaction(SIGUSR1, &cact, NULL);

    int i;
    for (i = 0; i < d; i++) {
        child_pid = fork();
        if (child_pid != 0) {
            // Czekamy na procesy potomne az zakoncza wypisywanie na standardowe
            // wyjscie.
            pause();
        } else {
            fflush(stdout);
            if (++j >= h - 1) { break; }
            i = -1;
        }
    }
    if (j != 0) {
        usleep(10000);
        kill(getppid(), SIGUSR1);
    } else {
        printf("done\n");
    }

    pause();
    int status = 0;
    wait(&status);

    return 0;
}
