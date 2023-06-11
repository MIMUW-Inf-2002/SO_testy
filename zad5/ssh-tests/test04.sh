#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file"

echo exclusive, incorrect flag, should give EINVAL
$SSH_CMD_ROOT "cd /tests; ./exclusive $tmp_file 5 -1 22" || exit 1
