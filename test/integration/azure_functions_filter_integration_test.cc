#include "common/config/azure_functions_well_known_names.h"
#include "common/config/metadata.h"

#include "test/integration/http_integration.h"
#include "test/integration/integration.h"
#include "test/integration/utility.h"

namespace Envoy {

const std::string DEFAULT_AZURE_FUNCTIONS_FILTER =
    R"EOF(
name: io.solo.azure_functions
)EOF";

class AzureFunctionsFilterIntegrationTest
    : public HttpIntegrationTest,
      public testing::TestWithParam<Network::Address::IpVersion> {
public:
  AzureFunctionsFilterIntegrationTest()
      : HttpIntegrationTest(Http::CodecClient::Type::HTTP1, GetParam()) {}

  /**
   * Initializer for an individual integration test.
   */
  void initialize() override {
    config_helper_.addFilter(DEFAULT_AZURE_FUNCTIONS_FILTER);

    config_helper_.addConfigModifier([](envoy::config::bootstrap::v2::Bootstrap
                                            &bootstrap) {
      auto &azure_functions_cluster =
          (*bootstrap.mutable_static_resources()->mutable_clusters(0));

      auto *metadata = azure_functions_cluster.mutable_metadata();

      Config::Metadata::mutableMetadataValue(
          *metadata,
          Config::AzureFunctionsMetadataFilters::get().AZURE_FUNCTIONS,
          Config::AzureFunctionsMetadataKeys::get().HOST)
          .set_string_value("yourapp.azurewebsites.net");

      // TODO(yuval-k): use consts (filename mess)
      std::string functionalfilter = "io.solo.function_router";
      std::string functionsKey = "functions";

      // add the function spec in the cluster config.
      // TODO(yuval-k): extract this to help method (test utils?)
      ProtobufWkt::Struct *functionstruct =
          Config::Metadata::mutableMetadataValue(*metadata, functionalfilter,
                                                 functionsKey)
              .mutable_struct_value();

      ProtobufWkt::Value &functionstructspecvalue =
          (*functionstruct->mutable_fields())["funcname"];
      ProtobufWkt::Struct *functionsspecstruct =
          functionstructspecvalue.mutable_struct_value();

      (*functionsspecstruct
            ->mutable_fields())[Config::AzureFunctionsMetadataKeys::get().PATH]
          .set_string_value("/api/function?code=ApiKey");
    });

    config_helper_.addConfigModifier(
        [](envoy::config::filter::network::http_connection_manager::v2::
               HttpConnectionManager &hcm) {
          auto *metadata = hcm.mutable_route_config()
                               ->mutable_virtual_hosts(0)
                               ->mutable_routes(0)
                               ->mutable_metadata();
          std::string functionalfilter = "io.solo.function_router";
          std::string functionKey = "function";
          std::string clustername =
              hcm.route_config().virtual_hosts(0).routes(0).route().cluster();

          ProtobufWkt::Struct *clusterstruct =
              Config::Metadata::mutableMetadataValue(
                  *metadata, functionalfilter, clustername)
                  .mutable_struct_value();

          (*clusterstruct->mutable_fields())[functionKey].set_string_value(
              "funcname");
        });

    HttpIntegrationTest::initialize();

    codec_client_ =
        makeHttpConnection(makeClientConnection((lookupPort("http"))));
  }

  /**
   * Initializer for an individual integration test.
   */
  void SetUp() override { initialize(); }
};

INSTANTIATE_TEST_CASE_P(
    IpVersions, AzureFunctionsFilterIntegrationTest,
    testing::ValuesIn(TestEnvironment::getIpVersionsForTest()));

TEST_P(AzureFunctionsFilterIntegrationTest, Test1) {
  Http::TestHeaderMapImpl request_headers{
      {":method", "POST"}, {":authority", "www.solo.io"}, {":path", "/"}};

  sendRequestAndWaitForResponse(request_headers, 10, default_response_headers_,
                                10);

  std::string path = upstream_request_->headers().Path()->value().c_str();
  std::string host = upstream_request_->headers().Host()->value().c_str();

  EXPECT_EQ("yourapp.azurewebsites.net", host);
  EXPECT_EQ("/api/function?code=ApiKey", path);
}

} // namespace Envoy
