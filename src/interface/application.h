#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include <secret/keys_bank.h>
#include <virtfs/path.h>

namespace aegis::interface {
    class Application {
    public:
        Application() = default;
        using RequestUser = std::function<bool()>;

        virtfs::path cacheDir;
        virtfs::path shaderCache;
        virtfs::path keys;
        virtfs::path logs;
        virtfs::path nand;
        virtfs::path icons;

        static void checkDir(const virtfs::path& dir);
        void checkAndTouchDirectories(const virtfs::path& applicationPath, bool& checked);

        void initialize();
        void sanitizeRequests();
        void placeUserRequest(const std::string& request, RequestUser&& callback);
    private:
        // Enables the application handle exceptions without throw one
        std::unordered_map<std::string, RequestUser> userRequests{};

        secret::KeysBank keysBank;
        bool isInitialized{};
        bool isSanitized{};
    };

    inline std::unique_ptr<Application> app;
}