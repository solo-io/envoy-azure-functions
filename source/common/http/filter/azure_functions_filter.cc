#include "common/http/filter/azure_functions_filter.h"

#include "common/http/headers.h"

namespace Envoy {
namespace Http {

void AzureFunctionsFilter::onDestroy() {}

FilterHeadersStatus AzureFunctionsFilter::decodeHeaders(HeaderMap &headers,
                                                        bool) {
  modifyHeaders(headers);
  return FilterHeadersStatus::Continue;
}

FilterDataStatus AzureFunctionsFilter::decodeData(Buffer::Instance &, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus AzureFunctionsFilter::decodeTrailers(HeaderMap &) {
  return FilterTrailersStatus::Continue;
}

void AzureFunctionsFilter::setDecoderFilterCallbacks(
    StreamDecoderFilterCallbacks &callbacks) {
  UNREFERENCED_PARAMETER(callbacks);
}

bool AzureFunctionsFilter::retrieveFunction(
    const MetadataAccessor &meta_accessor) {
  current_function_ = function_retriever_.getFunction(meta_accessor);
  return current_function_.valid();
}

void AzureFunctionsFilter::modifyHeaders(HeaderMap &headers) const {
  headers.insertHost().value(generateHost());
  headers.insertPath().value(generatePath());
}

std::string AzureFunctionsFilter::generateHost() const {
  const auto &current_function = current_function_.value();
  return *current_function.app_ + ".azurewebsites.net";
}

std::string AzureFunctionsFilter::generatePath() const {
  const auto &current_function = current_function_.value();
  return "/api/" + *current_function.name_ +
         "?code=" + *current_function.api_key_;
}

} // namespace Http
} // namespace Envoy
