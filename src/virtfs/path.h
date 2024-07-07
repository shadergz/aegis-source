#pragma once

#include <filesystem>
namespace aegis::virtfs {
    class path {
    public:
        path() = default;
        explicit path(const std::string& storage) : fsPath(storage) { // NOLINT(*-pass-by-value)
        }
        path operator /(const std::string& concat) const {
            return path{fsPath + "/" + concat};
        }
        explicit operator std::string() const {
            return fsPath;
        }
        [[nodiscard]] auto get() const {
            return fsPath.c_str();
        }
        explicit operator std::filesystem::path() const {
            return {fsPath};
        }
    private:
        std::string fsPath;
    };
}