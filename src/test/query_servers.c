#include "common.h"

int node_pid[PID_MAX];
int node_count = 0;

static void dfs(pid_t pid) {
    node_pid[node_count++] = pid;
    for (int i = 0; i < PID_MAX; i++)
        if (ppid[i] == pid) dfs(i);
}

static pid_t get_random_node() { return node_pid[rand() % node_count]; }

#define RS   4
#define PM   5
#define VFS  7

int main() {
    init_ppid_table();

    int fork_tree_root = get_fork_tree_root();

    dfs(fork_tree_root);

    test_valid_pids(get_random_node(), PM);
    test_valid_pids(PM, get_random_node());
    test_valid_pids(PM, VFS);
    test_valid_pids(PM, RS);
    test_valid_pids(RS, VFS);
    test_valid_pids(RS, get_random_node());

    PUTS_OK_NEEDLE;
}
