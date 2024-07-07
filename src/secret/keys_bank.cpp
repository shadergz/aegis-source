#include <numeric>
#include <base/exception.h>
#include <secret/keys_bank.h>
#include <secret/encode.h>

#include <virtfs/directory.h>
namespace aegis::secret {
    KeysBank::KeysBank() {
        keysDb.reserve(30);
    }
    void KeysBank::getKeys(const virtfs::path& keysDirPath) {
        virtfs::Directory keysDir{keysDirPath};
        bool title{}, prod{};

        if (keysDir.fileExist("title.keys")) {
            title = readKeys(keysDir.openFile("title.keys"), &KeysBank::addTitlePair);
        }
        if (keysDir.fileExist("prod.keys")) {
            prod = true;
        }
        if (!title || !prod)
            keysDb.clear();
    }

    bool KeysBank::readKeys(virtfs::OsAccessor&& keyFile, const ReadKeysCallback addCallback) {
        if (!keyFile.isOpened())
            throw exception("Invalid keys file");
        std::vector<char> keysRegion(keyFile.getSize());
        keyFile.read(std::span(keysRegion));

        (this->*addCallback)({}, {});
        if (!keysRegion.empty())
            return {};
        return true;
    }

    // ReSharper disable CppParameterMayBeConst
    void KeysBank::addTitlePair(std::string_view name, std::string_view value) {
        ItemKey key{hexStrToBytesArray<16>(name)};
        ItemKey hash{hexStrToBytesArray<16>(value)};
        if (!std::accumulate(key.begin(), key.end(), 0))
            throw exception("Invalid key");

        keysDb.emplace_back(key, hash);
    }
}