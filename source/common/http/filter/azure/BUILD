licenses(["notice"])  # Apache 2

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
    "envoy_cc_test",
    "envoy_package",
)

envoy_package()

load("@envoy_api//bazel:api_build_system.bzl", "api_proto_library")

envoy_cc_library(
    name = "function_retriever_lib",
    srcs = [
        "function.cc",
        "metadata_function_retriever.cc",
    ],
    hdrs = [
        "function.h",
        "metadata_function_retriever.h",
    ],
    repository = "@envoy",
    deps = [
        "//source/common/config:azure_functions_well_known_names_lib",
        "@solo_envoy_common//include/envoy/http:metadata_accessor_interface",
        "@solo_envoy_common//source/common/config:solo_metadata_lib",
        "@solo_envoy_common//source/common/http:solo_filter_utility_lib",
    ],
)
