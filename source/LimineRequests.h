#ifndef LIMINEREQUESTS_H_
#define LIMINEREQUESTS_H_

#include <stdint.h>
#include <limine.h>

extern struct limine_stack_size_request stackSizeRequest;
extern struct limine_framebuffer_request framebufferRequest;

bool VerifyBaseRevision(void);
bool VerifyStackSizeRequest(void);
bool VerifyFramebufferRequest(void);

#endif  // LIMINEREQUESTS_H_

