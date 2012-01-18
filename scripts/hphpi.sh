#!/bin/bash -e

set -e

. "$(dirname "${BASH_SOURCE[0]}")/setup.sh"
"$HPHP_HOME/src/hphpi/hphpi" $@
