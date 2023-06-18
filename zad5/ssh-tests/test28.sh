#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "echo "hejka" > $tmp_file"

echo exclusive, lock and then write by different user should be blocked

pids=()
$SSH_CMD_FOO "cd /tests; sleep 0.5; ./exclusive $tmp_file 1 0 0 && sleep 1 && ./exclusive $tmp_file 3 0 0" & pids+=($!)
$SSH_CMD_ROOT "cd /tests; ./open_util $tmp_file 1 2 1 -1 13" & pids+=($!)

sleep 2
$SSH_CMD_ROOT "cd /tests; ./exclusive $tmp_file 3 -1 37 > /dev/null" # cleanup, no impact on result

wait_pids