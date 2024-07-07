#pragma once

#include <array>
#include <vector>
#include <dirent.h>

#include <virtfs/path.h>
#include <virtfs/device_stream.h>
namespace aegis::virtfs {
    using DirectoryEntry = dirent;

    class Directory final : public DeviceBacking {
    public:
        explicit Directory(const path& dir) : DeviceBacking(dir) {
            openStream();
        }
        bool fileExist(const std::string& target);
        [[nodiscard]] DeviceStream openFile(const std::string& target) const {
            return DeviceStream{osPath / target};
        }
    private:
        // Not implemented (unused)
        Size writeImpl(std::span<u8> input, Size offset) override {
            return {};
        }
        // Not implemented (unused)
        Size readImpl(std::span<u8> output, Size offset) override {
            return {};
        }
        void produceFlags() override;
        void populate();

        Size pos{},
            end{},
            cursor{};
        std::array<u8, 2048> entries{};
        std::vector<DirectoryEntry*> dire;
    };
}

