#!/bin/bash

PORT=10040
TMP_FILE=/tmp/tmp

ROOT_PASSWD=root

FOO_PASSWD=mimuwrules
FOO_PASSWD_CRYPT=saFKLiF4jRXiE

# colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No color

SSH_CMD_ROOT="sshpass -p $ROOT_PASSWD ssh -p $PORT root@localhost"
SSH_CMD_FOO="sshpass -p $FOO_PASSWD ssh -p $PORT foo@localhost"

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