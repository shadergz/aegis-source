#pragma once

#include <array>
#include <vector>
#include <string>

#include <base/types.h>
#include <virtfs/path.h>
namespace aegis::secret {
    struct ItemKey {
        std::array<u8, 16> data;
    };

    class KeysBank {
    public:
        KeysBank();
        using KeyPair = std::pair<std::string, ItemKey>;

        void getKeys(const virtfs::path& keysDirPath);
        [[nodiscard]] auto hasKeys() const {
            return !keysDb.empty();
        }
    private:
        std::vector<KeyPair> keysDb; // All pushed keys is stored here
    };
}
