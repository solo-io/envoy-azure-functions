#pragma once

#include <string>

#include "common/singleton/const_singleton.h"

namespace Envoy {
namespace Config {

// TODO(talnordan): TODO: Merge with
// envoy/source/common/config/well_known_names.h.

/**
 * Well-known http filter names.
 */
class AzureFunctionsFilterNameValues {
public:
  // Azure Functions filter
  const std::string AZURE_FUNCTIONS = "io.solo.azure_functions";
};

typedef ConstSingleton<AzureFunctionsFilterNameValues>
    AzureFunctionsFilterNames;

/**
 * Well-known metadata filter namespaces.
 */
class AzureFunctionsMetadataFilterValues {
public:
  // Filter namespace for Azure Functions Filter.
  const std::string AZURE_FUNCTIONS = "io.solo.azure_functions";
};

typedef ConstSingleton<AzureFunctionsMetadataFilterValues>
    AzureFunctionsMetadataFilters;

/**
 * Keys for AzureFunctionsMetadataFilterValues::AZURE_FUNCTIONS metadata.
 */
class AzureFunctionsMetadataKeyValues {
public:
  const std::string APP = "app";
  const std::string NAME = "name";
  const std::string API_KEY = "api_key";
};

typedef ConstSingleton<AzureFunctionsMetadataKeyValues>
    AzureFunctionsMetadataKeys;

} // namespace Config
} // namespace Envoy
