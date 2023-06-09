#!/bin/bash
source config.sh
tmp_file1="${TMP_FILE}_$(basename "$0" .sh)1"
tmp_file2="${TMP_FILE}_$(basename "$0" .sh)2"
tmp_file3="${TMP_FILE}_$(basename "$0" .sh)3"
tmp_file4="${TMP_FILE}_$(basename "$0" .sh)4"
tmp_file5="${TMP_FILE}_$(basename "$0" .sh)5"
tmp_file6="${TMP_FILE}_$(basename "$0" .sh)6"
tmp_file7="${TMP_FILE}_$(basename "$0" .sh)7"
tmp_file8="${TMP_FILE}_$(basename "$0" .sh)8"
tmp_file9="${TMP_FILE}_$(basename "$0" .sh)9"

$SSH_CMD_ROOT "touch $tmp_file1 $tmp_file2 $tmp_file3 $tmp_file4 \
                    $tmp_file5 $tmp_file6 $tmp_file7 $tmp_file8 $tmp_file9"

echo exclusive, more than 8 locks, should ENOLCK on ninth. If this test fails, maybe file is still locked from previous tests.
$SSH_CMD_ROOT "cd /tests;   ./exclusive $tmp_file1 1 0 0 && ./exclusive $tmp_file2 1 0 0 && \
                            ./exclusive $tmp_file3 1 0 0 && ./exclusive $tmp_file4 1 0 0 && \
                            ./exclusive $tmp_file5 1 0 0 && ./exclusive $tmp_file6 1 0 0 && \
                            ./exclusive $tmp_file7 1 0 0 && ./exclusive $tmp_file8 1 0 0 && \
                            ./exclusive $tmp_file9 1 -1 77"
res=$?
$SSH_CMD_ROOT "cd /tests;   ./exclusive $tmp_file1 3 0 0 && ./exclusive $tmp_file2 3 0 0 && \
                            ./exclusive $tmp_file3 3 0 0 && ./exclusive $tmp_file4 3 0 0 && \
                            ./exclusive $tmp_file5 3 0 0 && ./exclusive $tmp_file6 3 0 0 && \
                            ./exclusive $tmp_file7 3 0 0 && ./exclusive $tmp_file8 3 0 0 &&"

exit $res