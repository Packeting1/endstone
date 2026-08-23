// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace endstone::core {

class ConfigValue {
public:
    using List = std::vector<ConfigValue>;
    struct Mapping;
    using MappingPtr = std::shared_ptr<Mapping>;
    using Value = std::variant<bool, std::int64_t, double, std::string, List, MappingPtr>;

    ConfigValue() = default;
    explicit ConfigValue(Value value);
    [[nodiscard]] const Value &value() const;

private:
    Value value_;
};

struct ConfigValue::Mapping {
    std::map<std::string, ConfigValue> values;
};

class Config {
public:
    Config();
    explicit Config(std::string path);
    Config(Config const &) = delete;
    Config &operator=(Config const &) = delete;
    Config(Config &&) noexcept;
    Config &operator=(Config &&) noexcept;
    ~Config();

    [[nodiscard]] bool load(std::string path = "endstone.toml");
    [[nodiscard]] bool has(std::string_view path) const;
    [[nodiscard]] bool getBool(std::string_view path, bool fallback = false) const;
    [[nodiscard]] std::int64_t getInt(std::string_view path, std::int64_t fallback = 0) const;
    [[nodiscard]] double getDouble(std::string_view path, double fallback = 0.0) const;
    [[nodiscard]] std::string getString(std::string_view path, std::string fallback = {}) const;
    [[nodiscard]] std::vector<ConfigValue> getList(std::string_view path, std::vector<ConfigValue> fallback = {}) const;

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

}  // namespace endstone::core
