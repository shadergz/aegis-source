#include <fcntl.h>

#include <virtfs/device_stream.h>
namespace aegis::virtfs {
    DeviceStream::~DeviceStream() = default;

    Size DeviceStream::readImpl(std::span<u8> output, const Size offset) {
        return {};
    }
    Size DeviceStream::writeImpl(std::span<u8> input, const Size offset) {
        return {};
    }
    void DeviceStream::produceFlags() {
        flags = O_RDONLY | O_RDWR;
    }
}