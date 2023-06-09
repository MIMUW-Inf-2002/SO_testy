#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file"

echo exclusive, same user but from different shell should be able to unlock
pids=()
$SSH_CMD_ROOT "cd /tests; ./exclusive $tmp_file 1 0 0 && sleep 1" & pids+=($!)
$SSH_CMD_ROOT "cd /tests; sleep 0.5; ./exclusive $tmp_file 3 0 0" & pids+=($!)

wait_pids