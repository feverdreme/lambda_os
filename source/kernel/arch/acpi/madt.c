#include "madt.h"

MADT_t *find_madt() {
    return (MADT_t*)find_sdt(MADT_SIGNATURE);
}