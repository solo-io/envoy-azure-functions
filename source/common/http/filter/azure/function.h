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

  static Optional<Function> createFunction(Optional<const std::string *> host,
                                           Optional<const std::string *> path);

  const std::string *host_{};
  const std::string *path_{};

private:
  Function(const std::string *host, const std::string *path)
      : host_(host), path_(path) {}
};

} // namespace Azure
} // namespace Http
} // namespace Envoy
