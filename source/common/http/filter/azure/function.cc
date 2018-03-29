#include "common/http/filter/azure/function.h"

namespace Envoy {
namespace Http {
namespace Azure {

Optional<Function>
Function::createFunction(Optional<const std::string *> host,
                         Optional<const std::string *> path) {
  if (!host.valid() || !path.valid()) {
    return {};
  }
  return Optional<Function>({host.value(), path.value()});
}

} // namespace Azure
} // namespace Http
} // namespace Envoy
