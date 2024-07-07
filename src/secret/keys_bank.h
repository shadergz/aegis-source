#pragma once

#include <array>
#include <vector>

#include <base/types.h>
#include <virtfs/directory.h>
namespace aegis::secret {
    using ItemKey = std::array<u8, 16>;

    class KeysBank {
    public:
        KeysBank();
        using ReadKeysCallback = void (KeysBank::*)(std::string_view name, std::string_view value);
        using KeyPair = std::pair<ItemKey, ItemKey>;

        void getKeys(const virtfs::path& keysDirPath);
        bool readKeys(virtfs::OsAccessor&& keyFile, ReadKeysCallback addCallback);
        void addTitlePair(std::string_view name, std::string_view value);

        [[nodiscard]] auto hasKeys() const {
            return !keysDb.empty();
        }
    private:
        std::vector<KeyPair> keysDb; // (All pushed keys is stored here)
    };
}
