# Envoy Azure Functions filter

This project links an Azure Functions HTTP filter with the Envoy binary.
A new filter `io.solo.azure_functions` which redirects requests to Azure Functions is introduced.

## Building

To build the Envoy static binary:

```
$ bazel build //:envoy
```

## Testing

To run the all tests:

```
$ bazel test //test/...
```

To run the all tests in debug mode:

```
$ bazel test //test/... -c dbg
```

To run integration tests using a clang build:

```
$ CXX=clang++-5.0 CC=clang-5.0 bazel test -c dbg --config=clang-tsan //test/integration:azure_functions_filter_integration_test
```

## E2E

For the e2e test, your Azure Function App requires a funcction named "uppercase". Its source code can be found in `e2e/uppercase.cs`.

To run the e2e test:

```
$ echo "<yourapp>" > ~/tmp/azure-app
$ echo "<ApiKey>" > ~/tmp/azure-api-key
$ bazel test //e2e/...
```
