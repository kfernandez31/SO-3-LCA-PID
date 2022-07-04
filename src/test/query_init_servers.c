#include "common.h"

#define INIT 1
#define RS   4
#define PM   5
#define VFS  7

void test_init_query(pid_t other_pid) {
    verify_getlcapid_errno(other_pid, INIT, ESRCH);
    verify_getlcapid_errno(INIT, other_pid, ESRCH);
}

int main() {
    test_init_query(INIT);
    test_init_query(RS);
    test_init_query(PM);
    test_init_query(VFS);

    PUTS_OK_NEEDLE;
}
