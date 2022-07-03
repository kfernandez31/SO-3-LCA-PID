#include "common.h"

int node_pid[PID_MAX];
int node_count = 0;

static void dfs(pid_t pid) {
    node_pid[node_count++] = pid;
    for (int i = 0; i < PID_MAX; i++)
        if (ppid[i] == pid) dfs(i);
}

static pid_t get_random_node() { return node_pid[rand() % node_count]; }

#define ITERATIONS 100

int main() {
    init_ppid_table();

    int fork_tree_root = get_fork_tree_root();

    dfs(fork_tree_root);

    for (int it = 0; it < ITERATIONS; it++) {
        pid_t a = get_random_node();
        pid_t b = get_random_node();
        test_valid_pids(a, b);
    }

    PUTS_OK_NEEDLE;
}
