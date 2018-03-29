#!/bin/bash
#

set -e

./create_config.sh || ./e2e/create_config.sh

ENVOY=${ENVOY:-envoy}

$ENVOY -c ./envoy.yaml --log-level debug &
sleep 5

curl -v localhost:10000/azure --data '{"message": "solo.io"}' -H"content-type: application/json"|grep SOLO.IO

echo PASS
