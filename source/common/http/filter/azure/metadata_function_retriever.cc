#include "common/http/filter/azure/metadata_function_retriever.h"

#include "common/common/macros.h"
#include "common/config/azure_functions_well_known_names.h"
#include "common/config/solo_metadata.h"

namespace Envoy {
namespace Http {
namespace Azure {

using Config::SoloMetadata;

absl::optional<Function> MetadataFunctionRetriever::getFunction(
    const MetadataAccessor &metadataccessor) const {

  absl::optional<const ProtobufWkt::Struct *> maybe_upstream_spec =
      metadataccessor.getClusterMetadata();
  if (!maybe_upstream_spec.has_value()) {
    return {};
  }

  absl::optional<const ProtobufWkt::Struct *> maybe_function_spec =
      metadataccessor.getFunctionSpec();
  if (!maybe_function_spec.has_value()) {
    return {};
  }

  const ProtobufWkt::Struct &upstream_spec = *maybe_upstream_spec.value();
  absl::optional<const std::string *> host = SoloMetadata::nonEmptyStringValue(
      upstream_spec, Config::AzureFunctionsMetadataKeys::get().HOST);

  const ProtobufWkt::Struct &function_spec = *maybe_function_spec.value();
  absl::optional<const std::string *> path = SoloMetadata::nonEmptyStringValue(
      function_spec, Config::AzureFunctionsMetadataKeys::get().PATH);

  return Function::createFunction(host, path);
}

} // namespace Azure
} // namespace Http
} // namespace Envoy
