#pragma once

#include <virtfs/device_backing.h>
namespace aegis::virtfs {
    class DeviceStream final : public DeviceBacking {
    public:
        explicit DeviceStream(const path& handler) : DeviceBacking(handler) {
            openStream();
        }
        ~DeviceStream() override;

        void produceFlags() override;
    private:
        Size readImpl(std::span<u8> output, Size offset) override;
        Size writeImpl(std::span<u8> input, Size offset) override;
    };
}
