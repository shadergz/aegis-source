#pragma once

#include <stdexcept>
#include <vector>

#include <fmt/format.h>
namespace aegis {
    class exception final : std::runtime_error {
    public:
        template <typename... Args>
        explicit exception(fmt::format_string<Args...> format, Args&&... args) :
            std::runtime_error(fmt::format(format, std::forward<Args>(args)...)),
            stack(getStackFrame()) {
        }
    private:
        static std::vector<void*> getStackFrame() __attribute__((noinline));
        std::vector<void*> stack;
    };
}
