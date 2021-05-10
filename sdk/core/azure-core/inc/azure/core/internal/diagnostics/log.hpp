// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include "azure/core/diagnostics/logger.hpp"
#include "azure/core/dll_import_export.hpp"

#include <atomic>
#include <type_traits>

namespace Azure { namespace Core { namespace Diagnostics { namespace _internal {
  class Log final {
    using LogLevelInt = std::underlying_type<Logger::Level>::type;

    static_assert(
        std::is_same<int, LogLevelInt>::value == true && ATOMIC_INT_LOCK_FREE == 2,
        "Logger::Level values must be representable as lock-free");

    static_assert(ATOMIC_BOOL_LOCK_FREE == 2, "atomic<bool> must be lock-free");

    static AZ_CORE_DLLEXPORT std::atomic<bool> g_isLoggingEnabled;
    static AZ_CORE_DLLEXPORT std::atomic<LogLevelInt> g_logLevel;

    Log() = delete;
    ~Log() = delete;

  public:
    static bool ShouldWrite(Logger::Level level)
    {
      return g_isLoggingEnabled && static_cast<LogLevelInt>(level) >= g_logLevel;
    }

    static void Write(Logger::Level level, std::string const& message);

    static void EnableLogging(bool isEnabled);
    static void SetLogLevel(Logger::Level logLevel);
  };
}}}} // namespace Azure::Core::Diagnostics::_internal
