#include <application.h>

namespace aegis {
    void Application::checkDir(const fs::path& dir) {
        const std::filesystem::path& checkPath{dir};

        if (!std::filesystem::is_directory(checkPath)) {
            std::filesystem::create_directory(checkPath);
        }
    }

    void Application::testAndTouchDirectories(
        fs::path& applicationPath, bool& checked) {
        const std::filesystem::path& rootStorage{applicationPath};

        if (!std::filesystem::is_directory(rootStorage)) {
            return;
        }
        cacheDir = applicationPath;
        shaderCache = cacheDir / "shader_cache";
        checkDir(shaderCache);

        keys = cacheDir / "keys";
        checkDir(keys);
        logs = cacheDir / "logs";
        checkDir(logs);
        nand = cacheDir / "emulated_nand";
        checkDir(nand);
        icons = cacheDir / "icons";
        checkDir(icons);

        checked = true;
    }
}
