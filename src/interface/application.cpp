#include <base/exception.h>
#include <interface/application.h>

namespace aegis::interface {
    void Application::checkDir(const virtfs::path& dir) {
        const std::filesystem::path checkPath{dir};
        if (!is_directory(checkPath)) {
            create_directory(checkPath);
        }
    }

    void Application::checkAndTouchDirectories(
        const virtfs::path& applicationPath, bool& checked) {
        const std::filesystem::path rootStorage{applicationPath};
        if (!is_directory(rootStorage)) {
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

    void Application::placeUserRequest(const std::string& request, RequestUser&& callback) {
        if (userRequests.contains(request)) {
            return;
        }
        userRequests.emplace(request, callback);
    }
    void Application::sanitizeRequests() {
        if (isSanitized)
            return;
        const std::array<std::string, 1> validRequests {
            "keys_prod"
        };
        for (const auto& request : validRequests) {
            if (!userRequests.contains(request))
                return;
        }
        isSanitized = true;
    }
    void Application::initialize() {
        if (isInitialized)
            return;
        sanitizeRequests();
        if (!isSanitized)
            return;

        while (!keysBank.hasKeys()) {
            if (!userRequests["keys_prod"]())
                return;
            keysBank.getKeys(keys);
        }
        isInitialized = true;
    }
}
