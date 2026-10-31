// Shared helper for HAL (port) fakes in unit and integration tests.
// Data file: <BPB_HAL_FAKE_DATA_DIR>/<Suite>_<Case>.json, actual calls: <Suite>_<Case>_actual.json.

#ifndef BPB_HALFAKE_H
#define BPB_HALFAKE_H

#include <string>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

namespace BpbHalFake
{
    // Loads the expected calls of the running gtest case from dataDir and clears recorded calls.
    void Load(const std::string &dataDir);

    // Records the actual call and returns the expected entry at the same position
    // ({"function", "args", "return", "out"}), or an empty object when no entry is left.
    const nlohmann::json &Call(const std::string &function, const nlohmann::json &args);

    // Writes the recorded calls to <Suite>_<Case>_actual.json next to the expected file.
    void Save();

    // Compares recorded calls with expected calls (count, order, function, args).
    ::testing::AssertionResult Verify();
}

#endif /* BPB_HALFAKE_H */
