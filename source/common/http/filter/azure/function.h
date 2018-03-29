#pragma once

#include <map>
#include <string>
#include <tuple>

#include "envoy/common/optional.h"

#include "common/protobuf/utility.h"

namespace Envoy {
namespace Http {
namespace Azure {

struct Function {
  // TODO(talnordan): Remove this when we have a optional that can support types
  // without a default ctor.
  Function() {}

  static Optional<Function>
  createFunction(Optional<const std::string *> app,
                 Optional<const std::string *> name,
                 Optional<const std::string *> api_key);

  const std::string *app_{};
  const std::string *name_{};
  const std::string *api_key_{};

private:
  Function(const std::string *app, const std::string *name,
           const std::string *api_key)
      : app_(app), name_(name), api_key_(api_key) {}
};

} // namespace Azure
} // namespace Http
} // namespace Envoy
