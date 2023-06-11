#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
tmp_file2="${TMP_FILE}_$(basename "$0" .sh)_2"
$SSH_CMD_ROOT "touch $tmp_file"

echo 'exclusive, lock and then move (source) by different user should be blocked'

pids=()
$SSH_CMD_FOO "cd /tests; ./exclusive $tmp_file 1 0 0 && sleep 1 && ./exclusive $tmp_file 3 0 0" & pids+=($!)
$SSH_CMD_ROOT "sleep 0.5 && ! mv $tmp_file $tmp_file2" & pids+=($!)

wait_pids