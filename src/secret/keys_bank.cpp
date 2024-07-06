#include <secret/keys_bank.h>

#include <virtfs/directory.h>
namespace aegis::secret {
    KeysBank::KeysBank() {
        keysDb.reserve(30);
    }
    void KeysBank::getKeys(const virtfs::path& keysDirPath) {
        virtfs::Directory keysDir{keysDirPath};
        bool title{}, prod{};

        if (keysDir.fileExist("title.keys")) {
            title = true;
        }
        if (keysDir.fileExist("prod.keys")) {
            prod = true;
        }
        if (!title || !prod)
            keysDb.clear();
    }
}