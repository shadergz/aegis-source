#pragma once

#include <virtfs/os_accessor.h>
namespace aegis::virtfs {
    class DeviceBacking : public OsAccessor {
    public:
        explicit DeviceBacking(const path& handler) : OsAccessor(handler) {
        }
        ~DeviceBacking() override;
        [[nodiscard]] bool isOpened() const override;
        bool isChanged() override;
        bool openStream();

    protected:
        IoSyncInfo status{};
        i32 fd{};
        i32 flags{};
        bool first{true};
    };
}
