#include <fcntl.h>
#include <unistd.h>

#include <cstring>

#include <base/exception.h>
#include <virtfs/device_backing.h>
namespace aegis::virtfs {
    DeviceBacking::~DeviceBacking() {
        if (fd)
            close(fd);
    }
    bool DeviceBacking::openStream() {
        if (isOpened())
            throw exception("A descriptor from the path {} is already opened", osPath.get());
        produceFlags();
        if (!flags)
            return {};
        fd = open(osPath.get(), flags);

        return isOpened() && isChanged();
    }

    bool DeviceBacking::isChanged() {
        if (!isOpened()) {
            throw exception("File {} not opened", osPath.get());
        }
        IoSyncInfo local;
        fstat(fd, &local);
        const auto changed{local.st_atim.tv_nsec != status.st_atim.tv_nsec};
        size = local.st_size;
        if (first || changed) {
            std::memcpy(&status, &local, sizeof status);
            first = {};
        }
        return changed;
    }

    bool DeviceBacking::isOpened() const {
        return fd > 0 && !access(osPath.get(), F_OK);
    }
}
