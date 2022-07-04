#include "common.h"

#include <limits.h>

void test_invalid_pid(pid_t invalid_pid) {
    verify_getlcapid_errno(getpid(), invalid_pid, EINVAL);
    verify_getlcapid_errno(invalid_pid, getpid(), EINVAL);
    verify_getlcapid_errno(invalid_pid, invalid_pid, EINVAL);
}

int main() {
    int child_pid = s_fork();
    if (child_pid == 0) return 0;
    wait(0);

    test_invalid_pid(child_pid);
    test_invalid_pid(1234567);
    test_invalid_pid(INT_MAX);
    test_invalid_pid(INT_MIN);
    test_invalid_pid(-1);
    test_invalid_pid(-2);
    test_invalid_pid(-3);
    test_invalid_pid(-4);

    PUTS_OK_NEEDLE;
}
