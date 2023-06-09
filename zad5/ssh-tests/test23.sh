#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file"

echo exclusive, lock and then unlink by different user should be blocked

pids=()
$SSH_CMD_FOO "cd /tests; ./exclusive $tmp_file 1 0 0 && sleep 1 && ./exclusive $tmp_file 3 0 0" & pids+=($!)
$SSH_CMD_ROOT "sleep 0.5 && ! unlink $tmp_file" & pids+=($!)

wait_pids