#include "common/http/filter/azure/function.h"

namespace Envoy {
namespace Http {
namespace Azure {

absl::optional<Function>
Function::createFunction(absl::optional<const std::string *> host,
                         absl::optional<const std::string *> path) {
  if (!host.has_value() || !path.has_value()) {
    return {};
  }
  return absl::optional<Function>({host.value(), path.value()});
}

} // namespace Azure
} // namespace Http
} // namespace Envoy
