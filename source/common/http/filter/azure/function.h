#pragma once

#include <map>
#include <string>
#include <tuple>

#include "common/protobuf/utility.h"

#include "absl/types/optional.h"

namespace Envoy {
namespace Http {
namespace Azure {

struct Function {
  // TODO(talnordan): Remove this when we have a optional that can support types
  // without a default ctor.
  Function() {}

  static absl::optional<Function>
  createFunction(absl::optional<const std::string *> host,
                 absl::optional<const std::string *> path);

  const std::string *host_{};
  const std::string *path_{};

private:
  Function(const std::string *host, const std::string *path)
      : host_(host), path_(path) {}
};

} // namespace Azure
} // namespace Http
} // namespace Envoy
