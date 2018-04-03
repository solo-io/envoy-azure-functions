#pragma once

#include <string>

#include "envoy/http/filter.h"
#include "envoy/http/metadata_accessor.h"

#include "common/common/logger.h"
#include "common/http/filter/azure/metadata_function_retriever.h"

namespace Envoy {
namespace Http {

class AzureFunctionsFilter : public StreamDecoderFilter,
                             public FunctionalFilter,
                             public Logger::Loggable<Logger::Id::filter> {
public:
  // Http::StreamFilterBase
  void onDestroy() override;

  // Http::StreamDecoderFilter
  FilterHeadersStatus decodeHeaders(HeaderMap &headers, bool) override;
  FilterDataStatus decodeData(Buffer::Instance &, bool) override;
  FilterTrailersStatus decodeTrailers(HeaderMap &) override;
  void
  setDecoderFilterCallbacks(StreamDecoderFilterCallbacks &callbacks) override;

  // Http::FunctionalFilter
  bool retrieveFunction(const MetadataAccessor &meta_accessor) override;

private:
  inline void modifyHeaders(HeaderMap &headers) const;
  inline const std::string &getHost() const;
  inline const std::string &getPath() const;

  Azure::MetadataFunctionRetriever function_retriever_;
  absl::optional<Azure::Function> current_function_;
};

} // namespace Http
} // namespace Envoy
