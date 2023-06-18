#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file; chmod 222 $tmp_file"

echo exclusive, file having only write permission, should succeed
$SSH_CMD_FOO "cd /tests; ./exclusive $tmp_file 1 0 0 && ./exclusive $tmp_file 3 0 0;" || exit 1
