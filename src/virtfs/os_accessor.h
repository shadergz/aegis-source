#pragma once
#include <span>

#include <sys/stat.h>

#include <base/types.h>
#include <virtfs/path.h>
namespace aegis::virtfs {
    using IoSyncInfo = struct stat;
    class OsAccessor {
    public:
        explicit OsAccessor(const path& path) : // NOLINT(*-pass-by-value)
            osPath(path) {}
        virtual ~OsAccessor() = default;

        virtual bool isChanged() = 0;
        [[nodiscard]] virtual bool isOpened() const = 0;

        [[nodiscard]] auto getSize() const {
            return size;
        };
        Size read(const std::span<u8> output, const Size offset = {}) {
            if (isOpened())
                return readImpl(output, offset);
            return {};
        }
        Size write(const std::span<u8> input, const Size offset = {}) {
            if (isOpened())
                return readImpl(input, offset);
            return {};
        }
        template <typename T> requires (!std::is_same_v<T, u8>)
        Size read(const std::span<T> output, const Size offset = {}) {
            return read(std::span(reinterpret_cast<u8*>(output.data()), output.size()), offset);
        }
    protected:
        virtual Size readImpl(std::span<u8> output, Size offset) = 0;
        virtual Size writeImpl(std::span<u8> input, Size offset) = 0;
        virtual void produceFlags() = 0;

        const path osPath;
        Size size{};
    };
}