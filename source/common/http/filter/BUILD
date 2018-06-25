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
    name = "azure_functions_filter_lib",
    srcs = ["azure_functions_filter.cc"],
    hdrs = ["azure_functions_filter.h"],
    repository = "@envoy",
    deps = [
        "//source/common/config:azure_functions_well_known_names_lib",
        "//source/common/http/filter/azure:function_retriever_lib",
        "@solo_envoy_common//source/common/http:functional_stream_decoder_base_lib",
    ],
)
