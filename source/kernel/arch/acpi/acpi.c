#include "acpi.h"

#include <limine_requests.h>

struct limine_rsdp_response rsdp_response;

int detect_rsdp_revision() {
    rsdp_response = *(rsdp_request.response);

    RSDP_Descriptor_t rsdp = *(RSDP_Descriptor_t*)(rsdp_response.address);
    return rsdp.revision;
}