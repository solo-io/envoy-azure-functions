#pragma once

#include <memory>

#include "envoy/http/metadata_accessor.h"

#include "common/http/filter/azure/function.h"

namespace Envoy {
namespace Http {
namespace Azure {

class MetadataFunctionRetriever {
public:
  Optional<Function> getFunction(const MetadataAccessor &metadataccessor) const;
};

} // namespace Azure
} // namespace Http
} // namespace Envoy
