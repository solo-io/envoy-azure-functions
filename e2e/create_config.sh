#!/bin/bash
#

set -e

APP=$(cat ~/tmp/azure-app)

ADDRESS=$APP
ADDRESS+=".azurewebsites.net"

API_KEY=$(cat ~/tmp/azure-api-key)

FUNCTION_HOST=$ADDRESS

FUNCTION_PATH="/api/uppercase?code="
FUNCTION_PATH+=$API_KEY

# prepare envoy config file.

cat > envoy.yaml << EOF
admin:
  access_log_path: /dev/stdout
  address:
    socket_address:
      address: 127.0.0.1
      port_value: 19000
static_resources:
  listeners:
  - name: listener_0
    address:
      socket_address: { address: 127.0.0.1, port_value: 10000 }
    filter_chains:
    - filters:
      - name: envoy.http_connection_manager
        config:
          stat_prefix: http
          codec_type: AUTO
          route_config:
            name: local_route
            virtual_hosts:
            - name: local_service
              domains: ["*"]
              routes:
              - match:
                  prefix: /azure
                route:
                  cluster: azure-function-app-1
                metadata:
                  filter_metadata:
                      io.solo.function_router:
                        azure-function-app-1:
                          function: uppercase
          http_filters:
          - name: io.solo.azure_functions
          - name: envoy.router
  clusters:
  - connect_timeout: 5.000s
    hosts:
    - socket_address:
        address: $ADDRESS
        port_value: 443
    name: azure-function-app-1
    type: LOGICAL_DNS
    dns_lookup_family: V4_ONLY
    tls_context: {}
    metadata:
      filter_metadata:
        io.solo.function_router:
          functions:
            uppercase:
              host: $FUNCTION_HOST
              path: $FUNCTION_PATH
        io.solo.azure_functions: {}
EOF
