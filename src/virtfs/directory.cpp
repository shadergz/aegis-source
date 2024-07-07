#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <virtfs/directory.h>
namespace aegis::virtfs {
    bool Directory::fileExist(const std::string& target) {
        populate();
        bool exist{};
        for (const auto entry : dire) {
            if (std::string_view(entry->d_name) == target)
                exist = true;
        }
        return exist;
    }
    void Directory::produceFlags() {
        flags = O_RDONLY | O_DIRECTORY;
    }

    void Directory::populate() {
        if (!isChanged() && !dire.empty())
            return;

        pos = end = cursor = {};
        end = syscall(SYS_getdents64, fd, entries.data(), entries.size());
        size = end;
        if (end <= 0)
            return;
        while (pos < end) {
            auto entry{reinterpret_cast<DirectoryEntry*>(entries.data() + pos)};
            dire.push_back(entry);
            pos += entry->d_reclen;
            cursor = entry->d_off;
        }
    }
}