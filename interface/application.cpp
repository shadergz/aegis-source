#include <application.h>

namespace aegis {
    void Application::checkDir(const fs::path& dir) {
        if (const std::filesystem::path& checkPath{dir}; !is_directory(checkPath)) {
            create_directory(checkPath);
        }
    }

    void Application::testAndTouchDirectories(
        const fs::path& applicationPath, bool& checked) {
        if (const std::filesystem::path& rootStorage{applicationPath};
            !is_directory(rootStorage)) {
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
