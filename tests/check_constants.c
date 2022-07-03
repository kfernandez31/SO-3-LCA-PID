#include "common.h"
#include <minix/callnr.h>

// This might have some false negatives. Should be verified manually where
// needed.
int main()
{
	_verify(PM_GETLCAPID > PM_BASE + 47, "invalid PM_GETLCAPID");
	_verify(NR_PM_CALLS > 48, "invalid NR_PM_CALLS");

	PUTS_OK_NEEDLE;
}
