#include "acpi.h"

#include <limine_requests.h>
#include <libc/string.h>

struct limine_rsdp_response rsdp_response;

int detect_rsdp_revision() {
    rsdp_response = *(rsdp_request.response);

    RSDP_Descriptor_t rsdp = *(RSDP_Descriptor_t*)(rsdp_response.address);
    return rsdp.revision;
}

RSDT_t *find_rsdt() {
    rsdp_response = *(rsdp_request.response);
    RSDP_Descriptor_t* rsdp = (RSDP_Descriptor_t*)(rsdp_response.address);
    return (RSDT_t*)(rsdp->rsdt_address);
}

void *find_sdt(const char *signature) {
    RSDT_t *rsdt_ptr = find_rsdt();

    int rsdt_num_entries = (rsdt_ptr->header.length - sizeof(ACPI_SDT_Header_t)) / sizeof(uint32_t);
    uint32_t *SDT = &rsdt_ptr->SDT_pointers;

    for (int i=0; i<rsdt_num_entries; i++) {
        ACPI_SDT_Header_t *acpi_sdt_header = (ACPI_SDT_Header_t*)(SDT[i]);

        if(!strncmp(acpi_sdt_header->signature, signature, 4))
            return (void*)(acpi_sdt_header);
    }

    return NULL;
}