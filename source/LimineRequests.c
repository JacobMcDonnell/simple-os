#include <stdint.h>
#include <limine.h>
#include "LimineRequests.h"

__attribute__((used, section(".limine_requests_start")))
LIMINE_REQUESTS_START_MARKER

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3)

bool VerifyBaseRevision(void) {
    return (limine_base_revision[2] == 0);
}

__attribute__((used, section(".limine_requests")))
struct limine_stack_size_request stackSizeRequest = {
    LIMINE_STACK_SIZE_REQUEST,
    0,
    nullptr,
    //0xFFFF
    0x100000
};

bool VerifyStackSizeRequest(void) {
    return ((stackSizeRequest.response != nullptr) &&
            (stackSizeRequest.response->revision >= stackSizeRequest.revision));
}

__attribute__((used, section(".limine_requests")))
struct limine_framebuffer_request framebufferRequest = {
    LIMINE_FRAMEBUFFER_REQUEST,
    0,
    nullptr
};

bool VerifyFramebufferRequest(void) {
    return ((framebufferRequest.response != nullptr) &&
            (framebufferRequest.response->framebuffer_count > 0) &&
            (framebufferRequest.response->revision >=
             framebufferRequest.revision));
}

__attribute__((used, section(".limine_requests_end")))
LIMINE_REQUESTS_END_MARKER

