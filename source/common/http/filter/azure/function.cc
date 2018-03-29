#include "common/http/filter/azure/function.h"

namespace Envoy {
namespace Http {
namespace Azure {

Optional<Function>
Function::createFunction(Optional<const std::string *> app,
                         Optional<const std::string *> name,
                         Optional<const std::string *> api_key) {
  if (!app.valid() || !name.valid() || !api_key.valid()) {
    return {};
  }
  return Optional<Function>({app.value(), name.value(), api_key.value()});
}

} // namespace Azure
} // namespace Http
} // namespace Envoy
