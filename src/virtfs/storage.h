#pragma once

#include <unistd.h>
#include <sys/stat.h>

#include <aegis/types.h>
#include <virtfs/path.h>
namespace aegis::virtfs {
    using StorageInfo = struct stat;

    class Storage {
    public:
        explicit Storage(const path& location);
        void reset();

        ~Storage() {
            if (valid()) // Descriptors with 0 value isn't valid
                close(vFd);
        }
        // Self create at specified location (path)
        bool create(bool dir);

        [[nodiscard]] bool valid() const {
            return vFd > 0;
        }
        bool exist() {
            sanitize();
            return valid();
        }

        void mkFlags(bool dir);
        void sanitize();
    protected:
        i32 vFd{};
        i32 osFlags{};
        StorageInfo status{};
        bool changed{}; // Indicates what file was modified after opened
        bool first{true};

        const std::string strPath;
    };

}
