#pragma once

namespace aegis::host {
    struct StackFrame {
        StackFrame* next;
        void* link;
    };
#if defined(ANDROID) && defined(__aarch64__)
    class ScopedBarrier {
    public:
        __attribute__((noinline)) ScopedBarrier() {
            StackFrame* frame{};
            __asm("mov %0, fp" : "=r" (frame));
            savedFrame = *frame;
            if (!frame)
                return;
            frame->next = {};
            frame->link = {};
        }
        __attribute__((noinline)) ~ScopedBarrier() {
            StackFrame* frame;
            __asm("mov %0, fp" : "=r" (frame));
            if (frame)
                *frame = savedFrame;
        }
    private:
        StackFrame savedFrame{};
    };
#else
    class ScopedBarrier{};
#endif
}
