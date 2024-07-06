#pragma once

namespace aegis::host {
    struct StackFrame {
        StackFrame* next;
        void* link;
    };
#if defined(ANDROID) && defined(__aarch64__)
    __attribute__((always_inline)) inline void getStack(StackFrame** stack) {
        __asm("mov %0, fp" : "=r" (*stack));
    }

    class ScopedBarrier {
    public:
        __attribute__((noinline)) ScopedBarrier()  {
            StackFrame* frame{};
            getStack(&frame);
            savedFrame = *frame;
            if (!frame)
                return;
            frame->next = {};
            frame->link = {};
        }
        __attribute__((noinline)) ~ScopedBarrier() {
            StackFrame* frame;
            getStack(&frame);
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
