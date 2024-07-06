#pragma once

#include <memory>

#include <secret/keys_bank.h>
#include <virtfs/path.h>

namespace aegis::interface {
    class Application {
    public:
        Application() = default;

        virtfs::path cacheDir;
        virtfs::path shaderCache;
        virtfs::path keys;
        virtfs::path logs;
        virtfs::path nand;
        virtfs::path icons;

        static void checkDir(const virtfs::path& dir);
        void checkAndTouchDirectories(const virtfs::path& applicationPath, bool& checked);

        void initialize();
    private:
        secret::KeysBank keysBank;
    };

    inline std::unique_ptr<Application> app;
}