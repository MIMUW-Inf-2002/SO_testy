#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file"

echo exclusive, EXCL_LOCK_NO_OTHERS should lock because same user is using

pids=()
$SSH_CMD_ROOT "cd /tests; sleep 0.5; ./exclusive $tmp_file 2 0 0 && ./exclusive $tmp_file 3 0 0" & pids+=($!)
$SSH_CMD_ROOT "cd /tests; ./open_util $tmp_file 1 0 1 0 0" & pids+=($!)

sleep 2
$SSH_CMD_ROOT "cd /tests; ./exclusive $tmp_file 3 -1 37 > /dev/null" # cleanup, no impact on result

wait_pids
