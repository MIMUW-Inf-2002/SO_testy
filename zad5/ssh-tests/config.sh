#!/bin/bash

PORT=10022
SSH_KEY="~/.ssh/id_ed2"
TMP_FILE=/tmp/tmp

# colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

SSH_CMD_ROOT="ssh -i $SSH_KEY -p $PORT root@localhost"
SSH_CMD_FOO="ssh -i $SSH_KEY -p $PORT foo@localhost"

# Testy potrzebują równoległego wykonywania poleceń,
# więc musimy przechwycić ich return code.
# Jeśli choć jeden zwrócił błąd, to zwracamy błąd.
function wait_pids {
    error=false
    for pid in ${pids[*]}; do
        if ! wait $pid; then
            error=true
        fi
    done
    if [ "$error" = true ]; then
        return 1
    fi
    return 0
}