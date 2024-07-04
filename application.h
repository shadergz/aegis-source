#pragma once

#include <filesystem>
#include <memory>
#include <utility>

namespace aegis::fs {
    class path {
    public:
        path() = default;
        path(const std::string& storage) : fsPath(storage) {
        }
        path operator /(const std::string& concat) const {
            return {fsPath + "/" + concat};
        }

        explicit operator std::filesystem::path() const {
            return {fsPath};
        }
    private:
        std::string fsPath;
    };
}

namespace aegis {
    class Application {
    public:
        Application() = default;

        fs::path cacheDir;
        fs::path shaderCache;
        fs::path keys;
        fs::path logs;
        fs::path nand;
        fs::path icons;

        static void checkDir(const fs::path& dir);
        void testAndTouchDirectories(fs::path& applicationPath, bool& checked);
    };

    inline std::unique_ptr<Application> app;
}