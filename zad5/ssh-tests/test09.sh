#!/bin/bash
source config.sh
tmp_file="${TMP_FILE}_$(basename "$0" .sh)"
tmp_file2="${TMP_FILE}_$(basename "$0" .sh)_2"
$SSH_CMD_FOO "touch $tmp_file"

echo exclusive, lock file and renaming it, should remain locked
$SSH_CMD_FOO "cd /tests;    ./exclusive $tmp_file 1 0 0 && mv $tmp_file $tmp_file2 && \
                            ./exclusive $tmp_file2 1 -1 37 && ./exclusive $tmp_file2 3 0 0" || exit 1
