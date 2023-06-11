#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file"

echo exclusive, force unlock should EPERM because none of the above

pids=()
$SSH_CMD_ROOT "cd /tests; ./exclusive $tmp_file 1 0 0 && sleep 1 && ./exclusive $tmp_file 4 0 0" & pids+=($!)
$SSH_CMD_FOO "cd /tests; sleep 0.5; ./exclusive $tmp_file 4 -1 1 && ! cat $tmp_file" & pids+=($!)

wait_pids