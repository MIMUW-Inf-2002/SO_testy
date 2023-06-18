#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
$SSH_CMD_ROOT "touch $tmp_file"

echo fexclusive, simple lock unlock 

$SSH_CMD_FOO "cd /tests; ./fexclusive $tmp_file 1 3 0 0 0 0 0" || exit 1

