#include <cstring>
#include <fcntl.h>

#include <virtfs/storage.h>
namespace aegis::virtfs {
    Storage::Storage(const path& location) : strPath(std::string(location)) {
        mkFlags(true);
        vFd = open(strPath.c_str(), osFlags);
        if (!valid() && !access(strPath.c_str(), F_OK)) {
            mkFlags(false);
            vFd = open(strPath.c_str(), osFlags);
        }
        if (!valid()) {
            reset();
        }
    }
    void Storage::reset() {
        first = {};
        vFd = osFlags = {};
        changed = {};
        status = {};
    }
    bool Storage::create(const bool dir) {
        reset();
        mkFlags(dir);

        vFd = open(strPath.c_str(), osFlags);
        return exist();
    }
    void Storage::mkFlags(const bool dir) {
        osFlags = O_RDONLY;
        if (dir)
            osFlags |= O_DIRECTORY;
    }

    void Storage::sanitize() {
        StorageInfo local;
        if (!valid()) {
            vFd = {};
            status = {};
            return;
        }
        fstat(vFd, &local);
        if (first) {
            std::memcpy(&status, &local, sizeof status);
            first = {};
        } else {
            changed = local.st_atim.tv_nsec != status.st_atim.tv_nsec;
        }
    }

}