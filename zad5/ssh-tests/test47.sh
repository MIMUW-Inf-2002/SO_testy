#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file"

echo exclusive, EXCL_LOCK_NO_OTHERS should fail because foo is using

$SSH_CMD_ROOT "cd /tests; ./exclusive $tmp_file 3 -1 37 > /dev/null" # cleanup, no impact on result

pids=()
$SSH_CMD_FOO "cd /tests; sleep 0.5; ./exclusive $tmp_file 2 -1 35" & pids+=($!)
$SSH_CMD_ROOT "cd /tests; ./open_util $tmp_file 1 0 1 0 0" & pids+=($!)

wait_pids
