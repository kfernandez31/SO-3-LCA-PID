#include "common.h"

int node_pid[PID_MAX];
int node_count = 0;

static void dfs(pid_t pid) {
    node_pid[node_count++] = pid;
    for (int i = 0; i < PID_MAX; i++)
        if (ppid[i] == pid) dfs(i);
}

static pid_t get_random_node() { return node_pid[rand() % node_count]; }

#define INIT 1
#define ITERATIONS 10

void test_init_query(pid_t other_pid) {
    verify_getlcapid_errno(other_pid, INIT, ESRCH);
    verify_getlcapid_errno(INIT, other_pid, ESRCH);
}

int main() {
    init_ppid_table();

    int fork_tree_root = get_fork_tree_root();

    dfs(fork_tree_root);

    for(int i = 0; i < ITERATIONS; i++)
        test_init_query(get_random_node());

    PUTS_OK_NEEDLE;
}
