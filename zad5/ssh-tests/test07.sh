#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file; chmod 000 $tmp_file"

echo exclusive, not having permission to open file, should EACCES
$SSH_CMD_FOO "cd /tests; ./exclusive $tmp_file 1 -1 13" || exit 1
