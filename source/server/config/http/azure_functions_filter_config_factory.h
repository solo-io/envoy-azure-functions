#pragma once

#include "common/config/azure_functions_well_known_names.h"

#include "extensions/filters/http/common/empty_http_filter_config.h"

namespace Envoy {
namespace Server {
namespace Configuration {

using Extensions::HttpFilters::Common::EmptyHttpFilterConfig;

/**
 * Config registration for the Azure Functions filter.
 */
class AzureFunctionsFilterConfigFactory : public EmptyHttpFilterConfig {
public:
  AzureFunctionsFilterConfigFactory()
      : EmptyHttpFilterConfig(
            Config::AzureFunctionsFilterNames::get().AZURE_FUNCTIONS) {}

  Http::FilterFactoryCb createFilter(const std::string &stat_prefix,
                                     FactoryContext &context) override;
};

} // namespace Configuration
} // namespace Server
} // namespace Envoy
