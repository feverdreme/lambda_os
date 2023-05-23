#include "acpi.h"

#include <limine_requests.h>
#include <libc/string.h>

struct limine_rsdp_response rsdp_response;

int detect_rsdp_revision() {
    rsdp_response = *(rsdp_request.response);

    RSDP_Descriptor_t rsdp = *(RSDP_Descriptor_t*)(rsdp_response.address);
    return rsdp.revision;
}

void *find_sdt(RSDT_t *rsdt_ptr, const char *signature) {
    int rsdt_num_entries = (rsdt_ptr->header.length - sizeof(rsdt_ptr->header)) / 4;

    for (int i=0; i<rsdt_num_entries; i++) {
        ACPI_SDT_Header_t *acpi_sdt_header = (ACPI_SDT_Header_t*)(rsdt_ptr->SDT_pointers[i]);

        if(!strncmp(acpi_sdt_header->signature, signature, 4))
            return (void*)(rsdt_ptr->SDT_pointers[i]);
    }

    return NULL;
}