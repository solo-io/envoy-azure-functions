licenses(["notice"])  # Apache 2

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
    "envoy_cc_test",
    "envoy_package",
)

envoy_package()

envoy_cc_library(
    name = "azure_functions_filter_config_lib",
    srcs = ["azure_functions_filter_config_factory.cc"],
    hdrs = ["azure_functions_filter_config_factory.h"],
    repository = "@envoy",
    deps = [
        "//source/common/config:azure_functions_well_known_names_lib",
        "//source/common/http/filter:azure_functions_filter_lib",
        "@envoy//include/envoy/registry",
        "@envoy//include/envoy/server:filter_config_interface",
        "@envoy//source/extensions/filters/http/common:empty_http_filter_config_lib",
    ],
)
