#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file"

echo exclusive, lock and then open by different user should be blocked

pids=()
$SSH_CMD_FOO "cd /tests; ./exclusive $tmp_file 1 0 0 && sleep 1 && ./exclusive $tmp_file 3 0 0" & pids+=($!)
$SSH_CMD_ROOT "sleep 0.5 && ! cat $tmp_file" & pids+=($!) # aby zrobić negację return code'u cat'a

wait_pids