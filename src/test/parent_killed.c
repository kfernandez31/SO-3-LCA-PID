#include "common.h"

int main() {
    int fd[2];
    pipe(fd);

    int root_pid = getpid();
    int child_pid = s_fork();

    if (child_pid == 0) {
        close(fd[0]);

        child_pid = s_fork();
        if (child_pid == 0) {
            close(fd[1]);

            // testing while parent is still alive
            init_ppid_table();
            test_valid_pids(root_pid, getpid()); 

            // keeping child alive
            while (true) {}
        } else {
            write(fd[1], &child_pid, sizeof(int));
            close(fd[1]);

            sleep(1); // keeping parent alive
        }
    } else {
        close(fd[1]);

        sleep(2); // waiting untill child becomes zombie
        init_ppid_table();
        test_valid_pids(root_pid, child_pid);

        wait(0);
       
        // reading pid of child of the child
        read(fd[0], &child_pid, sizeof(int));
        close(fd[0]);

        init_ppid_table();
        test_valid_pids(root_pid, child_pid);

        kill(child_pid, SIGKILL);
    
        PUTS_OK_NEEDLE;
    }
}
