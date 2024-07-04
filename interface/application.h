#pragma once

#include <filesystem>
#include <memory>

namespace aegis::fs {
    class path {
    public:
        path() = default;
        explicit path(const std::string& storage) : fsPath(storage) { // NOLINT(*-pass-by-value)
        }
        path operator /(const std::string& concat) const {
            return path{fsPath + "/" + concat};
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
        void testAndTouchDirectories(const fs::path& applicationPath, bool& checked);
    };

    inline std::unique_ptr<Application> app;
}