#pragma once

#include "envoy/server/filter_config.h"

namespace Envoy {
namespace Server {
namespace Configuration {

class AzureFunctionsFilterConfigFactory : public NamedHttpFilterConfigFactory {
public:
  // Server::Configuration::NamedHttpFilterConfigFactory
  HttpFilterFactoryCb createFilterFactory(const Json::Object &config,
                                          const std::string &stat_prefix,
                                          FactoryContext &context) override;
  HttpFilterFactoryCb
  createFilterFactoryFromProto(const Protobuf::Message &config,
                               const std::string &stat_prefix,
                               FactoryContext &context) override;
  ProtobufTypes::MessagePtr createEmptyConfigProto() override;
  std::string name() override;
};

} // namespace Configuration
} // namespace Server
} // namespace Envoy
