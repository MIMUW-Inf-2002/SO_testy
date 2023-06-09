#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file"

echo exclusive, one user locks, other tries to unlock, should EPERM

pids=()
$SSH_CMD_ROOT "cd /tests; ./exclusive $tmp_file 1 0 0 && sleep 1 && ./exclusive $tmp_file 3 0 0" & pids+=($!)
$SSH_CMD_FOO "cd /tests && sleep 0.5 && ./exclusive $tmp_file 1 -1 13 && ./exclusive $tmp_file 3 -1 1" & pids+=($!)

wait_pids