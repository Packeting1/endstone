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

#include "endstone/core/config.h"

#include <memory>
#include <utility>

#include <toml++/toml.h>

namespace endstone::core {

ConfigValue::ConfigValue(Value value) : value_(std::move(value)) {}

const ConfigValue::Value &ConfigValue::value() const
{
    return value_;
}

static ConfigValue convertValue(const toml::node &node)
{
    if (auto value = node.value<bool>()) {
        return ConfigValue(*value);
    }
    if (auto value = node.value<std::int64_t>()) {
        return ConfigValue(*value);
    }
    if (auto value = node.value<double>()) {
        return ConfigValue(*value);
    }
    if (auto value = node.value<std::string>()) {
        return ConfigValue(*value);
    }
    if (const auto *table = node.as_table()) {
        auto mapping = std::make_shared<ConfigValue::Mapping>();
        for (const auto &[key, item] : *table) {
            mapping->values.emplace(key, convertValue(item));
        }
        return ConfigValue(std::move(mapping));
    }
    if (const auto *array = node.as_array()) {
        ConfigValue::List result;
        result.reserve(array->size());
        for (const auto &item : *array) {
            result.emplace_back(convertValue(item));
        }
        return ConfigValue(std::move(result));
    }
    return ConfigValue(std::string{});
}

class Config::Impl {
public:
    toml::table table;
};

Config::Config() : impl_(std::make_unique<Impl>())
{
    (void)load();
}

Config::Config(std::string path) : impl_(std::make_unique<Impl>())
{
    (void)load(std::move(path));
}

Config::Config(Config &&) noexcept = default;
Config &Config::operator=(Config &&) noexcept = default;
Config::~Config() = default;

bool Config::load(std::string path)
{
    try {
        impl_->table = toml::parse_file(path);
        return true;
    }
    catch (const toml::parse_error &) {
        impl_->table = {};
        return false;
    }
}

bool Config::has(std::string_view path) const
{
    return static_cast<bool>(impl_->table.at_path(path));
}

bool Config::getBool(std::string_view path, bool fallback) const
{
    const auto node = impl_->table.at_path(path);
    return node ? node.value<bool>().value_or(fallback) : fallback;
}

std::int64_t Config::getInt(std::string_view path, std::int64_t fallback) const
{
    const auto node = impl_->table.at_path(path);
    return node ? node.value<std::int64_t>().value_or(fallback) : fallback;
}

double Config::getDouble(std::string_view path, double fallback) const
{
    const auto node = impl_->table.at_path(path);
    if (!node) {
        return fallback;
    }
    if (auto value = node.value<double>()) {
        return *value;
    }
    if (auto value = node.value<std::int64_t>()) {
        return static_cast<double>(*value);
    }
    return fallback;
}

std::string Config::getString(std::string_view path, std::string fallback) const
{
    const auto node = impl_->table.at_path(path);
    return node ? node.value<std::string>().value_or(std::move(fallback)) : fallback;
}

std::vector<ConfigValue> Config::getList(std::string_view path, std::vector<ConfigValue> fallback) const
{
    const auto node = impl_->table.at_path(path);
    const auto *array = node ? node.as_array() : nullptr;
    if (!array) {
        return fallback;
    }
    std::vector<ConfigValue> result;
    result.reserve(array->size());
    for (const auto &item : *array) {
        result.emplace_back(convertValue(item));
    }
    return result;
}

}  // namespace endstone::core
