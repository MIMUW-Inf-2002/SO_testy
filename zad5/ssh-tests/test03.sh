#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file"

echo exclusive, two unlocks, second should give EINVAL
$SSH_CMD_ROOT "cd /tests; ./exclusive $tmp_file 1 0 0  && ./exclusive $tmp_file 3 0 0 && ./exclusive $tmp_file 3 -1 22" || exit 1
