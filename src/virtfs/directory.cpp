#include <virtfs/directory.h>

#include <syscall.h>
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
    void Directory::populate() {
        sanitize();
        pos = end = cursor = {};
        if (!changed && !dire.empty())
            return;
        end = static_cast<i32>(syscall(SYS_getdents, vFd, entries.data(), entries.size()));
        if (end <= 0)
            return;

        while (pos < end) {
            auto entry{reinterpret_cast<DirectoryEntry*>(entries.data() + pos)};
            dire.push_back(entry);
            pos += entry->d_reclen;
            cursor = static_cast<i32>(entry->d_off);
        }
        changed = {};
    }
}