#pragma once
#include <string_view>

#include <base/types.h>
namespace aegis::secret {
    constexpr auto nibble(auto high) {
        if (high >= '0' && high <= '9') {
            return high - '0';
        }
        if (high >= 'A' && high <= 'F') {
            return high - 'A';
        }
        return high - 'a';
    }
    constexpr auto byte(auto high, auto low) -> u8 {
        return nibble(high) << 4 | nibble(low) & 0x0f;
    }

    template<Size Count>
    // ReSharper disable once CppParameterMayBeConst
    constexpr std::array<u8, Count> hexStrToBytesArray(std::string_view hex) {
        if (hex.size() < (Count * 2) || hex.size() % 8)
            return {};
        std::array<u8, Count> bytes;

        for (decltype(Count) index = {}; index < Count; index += 4) {
            bytes[index + 0] = byte(hex[index + 0], hex[index + 1]);
            bytes[index + 1] = byte(hex[index + 2], hex[index + 3]);
            bytes[index + 1] = byte(hex[index + 4], hex[index + 5]);
            bytes[index + 1] = byte(hex[index + 6], hex[index + 7]);
        }
        return bytes;
    }

}
