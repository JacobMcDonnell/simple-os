#include <stddef.h>
#include "limine.h"
#include "LimineRequests.h"
#include "memory.h"

static void HaltForever(void) {
    while (true) {
        asm("hlt");
    }
}

void KernelMain(void) {
    if (!VerifyBaseRevision()) {
        HaltForever();
    }

    if (!VerifyStackSizeRequest()) {
        HaltForever();
    }

    if (!VerifyFramebufferRequest()) {
        HaltForever();
    }

    const uint64_t framebufferCount =
        framebufferRequest.response->framebuffer_count;

    struct limine_framebuffer **framebuffers =
        framebufferRequest.response->framebuffers;

    struct limine_framebuffer *framebuffer = nullptr;

    const uint32_t colors[] = {0xFF0000, 0x00FF00, 0x0000FF};
    uint8_t count = 0;
    uint8_t color = 0;

    for (uint64_t i = 0; i < framebufferCount; i++) {
        framebuffer = framebuffers[i];
        volatile uint32_t *fb_ptr = (volatile uint32_t *)framebuffer->address;
        for (uint64_t j = 0; j < framebuffer->height && j < framebuffer->width;
                j++) {
            fb_ptr[j * (framebuffer->pitch / 4) + j] = colors[color];
            if ((count = (count + 1) % 16) == 0) {
                color = (color + 1) % 3;
            }
        }
    }

    HaltForever();
}

