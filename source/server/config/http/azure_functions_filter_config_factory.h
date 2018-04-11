#pragma once

#include "extensions/filters/http/common/empty_http_filter_config.h"

namespace Envoy {
namespace Server {
namespace Configuration {

class AzureFunctionsFilterConfigFactory
    : public Extensions::HttpFilters::Common::EmptyHttpFilterConfig {
public:
  // Server::Configuration::NamedHttpFilterConfigFactory
  std::string name() override;

  // Server::Configuration::EmptyHttpFilterConfig
  HttpFilterFactoryCb createFilter(const std::string &stat_prefix,
                                   FactoryContext &context) override;
};

} // namespace Configuration
} // namespace Server
} // namespace Envoy
