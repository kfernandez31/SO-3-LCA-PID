#include "common.h"

#include <limits.h>

#define INIT 1

void test_invalid_pid(pid_t invalid_pid) {
    verify_getlcapid_errno(INIT, invalid_pid, EINVAL);
    verify_getlcapid_errno(invalid_pid, INIT, EINVAL);
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
