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

api_proto_library(
    name = "azure_functions_filter_proto",
    srcs = ["azure_functions_filter.proto"],
)

envoy_cc_library(
    name = "filter_lib",
    repository = "@envoy",
    visibility = ["//visibility:public"],
    deps = [
        "//source/server/config/http:azure_functions_filter_config_lib",
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_binary(
    name = "envoy",
    repository = "@envoy",
    deps = [
        ":filter_lib",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)
