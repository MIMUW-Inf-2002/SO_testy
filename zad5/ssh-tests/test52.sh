#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file"

echo fexclusive, lock and unlock should release the file

$SSH_CMD_ROOT "cd /tests; ./exclusive $tmp_file 3 -1 37 > /dev/null" # cleanup, no impact on result

pids=()
$SSH_CMD_ROOT "cd /tests; ./fexclusive $tmp_file 1 3 0 0 0 0 0" & pids+=($!)
$SSH_CMD_FOO "cd /tests; sleep 0.5; cat $tmp_file" & pids+=($!)


wait_pids
