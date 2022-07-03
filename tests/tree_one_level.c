#include "common.h"

#define LEVEL 4

int node_pid[PID_MAX];
int node_count = 0;

static void dfs(pid_t pid, int depth) {
    if(depth == LEVEL)
        node_pid[node_count++] = pid;
    for (int i = 0; i < PID_MAX; i++)
        if (ppid[i] == pid) dfs(i, depth + 1);
}

static pid_t get_random_node() { return node_pid[rand() % node_count]; }

int main() {
    init_ppid_table();

    int fork_tree_root = get_fork_tree_root();

    dfs(fork_tree_root, 1);

    for (int i = 0; i < node_count; i++)
        for (int j = 0; j < node_count; j++)
            test_valid_pids(node_pid[i], node_pid[j]);

    PUTS_OK_NEEDLE;
}
