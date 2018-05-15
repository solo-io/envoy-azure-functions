#include "server/config/http/azure_functions_filter_config_factory.h"

#include "envoy/registry/registry.h"

#include "common/http/filter/azure_functions_filter.h"
#include "common/http/functional_stream_decoder_base.h"

namespace Envoy {
namespace Server {
namespace Configuration {

typedef Http::FunctionalFilterMixin<Http::AzureFunctionsFilter>
    MixedAzureFunctionsFilter;

Http::FilterFactoryCb
AzureFunctionsFilterConfigFactory::createFilter(const std::string &stat_prefix,
                                                FactoryContext &context) {
  UNREFERENCED_PARAMETER(stat_prefix);

  return [&context](Http::FilterChainFactoryCallbacks &callbacks) -> void {
    auto filter = new MixedAzureFunctionsFilter(
        context, Config::AzureFunctionsFilterNames::get().AZURE_FUNCTIONS);
    callbacks.addStreamDecoderFilter(
        Http::StreamDecoderFilterSharedPtr{filter});
  };
}

/**
 * Static registration for the Azure Functions filter. @see RegisterFactory.
 */
static Registry::RegisterFactory<AzureFunctionsFilterConfigFactory,
                                 NamedHttpFilterConfigFactory>
    register_;

} // namespace Configuration
} // namespace Server
} // namespace Envoy
