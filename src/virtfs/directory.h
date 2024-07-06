#pragma once

#include <array>
#include <vector>
#include <dirent.h>

#include <virtfs/storage.h>
namespace aegis::virtfs {
    using DirectoryEntry = dirent;

    class Directory : Storage {
    public:
        explicit Directory(const path& dir) : Storage(dir) {
            sanitize();
        }
        bool fileExist(const std::string& target);

    private:
        void populate();
        i32 pos{},
            end{},
            cursor{};
        std::array<u8, 2048> entries{};
        std::vector<DirectoryEntry*> dire;
    };
}

