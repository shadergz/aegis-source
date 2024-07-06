#include <base/types.h>
#include <base/exception.h>

#if !defined(ANDROID) && defined(__linux__)
#include <execinfo.h>
#else
#include <host/barrier.h>
#endif

namespace aegis {
    std::vector<void*> exception::getStackFrame() {
        std::vector<void*> frames{};
#if defined(ANDROID)
        host::StackFrame* frame{};
        getStackRegister(&frame);

        if (frame)
            frame = frame->next;
        while (frame) {
            frames.push_back(frame->link);
        }
#else
        constexpr i32 complexFrame{30};

        frames.resize(complexFrame);
        const auto entries{backtrace(frames.data(), complexFrame)};
        frames.resize(entries);
#endif

        return frames;
    }
}