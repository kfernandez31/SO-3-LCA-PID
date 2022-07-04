#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

static void fail() {
    fflush(stdout);
    fflush(stderr);
    kill(0, SIGKILL);
}

static void syserr(const char* msg) {
    perror(msg);
    fail();
}

static pid_t s_fork(void) {
    pid_t ret = fork();
    if (ret < 0) syserr("fork");
    return ret;
}

static pid_t s_wait(int* istat) {
    pid_t ret = wait(istat);
    if (ret < 0) syserr("wait");
    return ret;
}

static void _verify(bool b, const char* format, ...) {
    if (!b) {
        va_list ap;
        va_start(ap, format);
        vprintf(format, ap);
        va_end(ap);
        fail();
    }
}

static pid_t verify_getlcapid_errno(pid_t a, pid_t b, int expected) {
    errno = 0;
    pid_t result = getlcapid(a, b);
    _verify(errno == expected, "errno=%d,expected=%d", errno, expected);
    if (errno != 0) _verify(result == -1, "result=%d,expected=-1", result);
    return result;
}

static void verify_getlcapid_pid(pid_t a, pid_t b, int expected) {
    pid_t pid = verify_getlcapid_errno(a, b, 0);
    _verify(pid == expected, "pid=%d,expected=%d", pid, expected);
}

#define PID_MAX 30000

pid_t ppid[PID_MAX];
bool is_tree_proc[PID_MAX];

static void init_ppid_table() {
    FILE* f = popen("ps -lx", "r");
    char line[1024];

    for (int i = 0; i < PID_MAX; i++) ppid[i] = -1;

    fgets(line, sizeof(line), f); // read headers
    while (fgets(line, sizeof(line), f) != NULL) {
        // uid must be 0, then the next two numbers are pid and ppid
        int pos = 0;
        while (line[pos] != '0') pos++;
        pos++;

        int pid, parent;
        sscanf(line + pos, "%d %d", &pid, &parent);

        if (pid > 0) {
            ppid[pid] = parent;
            is_tree_proc[pid] = (strstr(line, "./fork_tree") != NULL);
        }
    }
}

bool is_ancestor[PID_MAX];

// assumes given pids exist
// must call init_ppid_table() first
static pid_t mylcapid(pid_t a, pid_t b) {
    pid_t cur = a;
    while (ppid[cur] != -1) {
        cur = ppid[cur];
        is_ancestor[cur] = false; // clean memory
    }

    cur = b;
    while (ppid[cur] != -1) {
        cur = ppid[cur];
        is_ancestor[cur] = true; // mark ancestors
    }

    cur = a;
    while (ppid[cur] != -1) {
        cur = ppid[cur];
        if (is_ancestor[cur]) // lowest common ancestor
            return cur;
    }

    return -1; // no lca
}

// must call init_ppid_table() first
static pid_t get_fork_tree_root() {
    for(pid_t i = 0; i < PID_MAX; i++)
        if(is_tree_proc[i] && !is_tree_proc[ppid[i]])
            return i;
    printf("get_fork_tree_root: root not found\n");
    fail();
    return -1; // mute warning
}

static void test_valid_pids(pid_t a, pid_t b) {
    pid_t expected = mylcapid(a, b);
    errno = 0;
    pid_t result = getlcapid(a, b);

    if (expected == -1)
        _verify(errno == ESRCH, "errno=%d,expected=%d", errno, ESRCH);
    else _verify(errno == 0, "errno=%d", errno);

    _verify(result == expected, "result=%d,expected=%d", result, expected);
}

#define PUTS_OK_NEEDLE puts("OK")
