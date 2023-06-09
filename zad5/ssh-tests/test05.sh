#!/bin/bash
source config.sh

echo exclusive, file is a direcotory or device, should EFTYPE
$SSH_CMD_ROOT "cd /tests; ./exclusive /tmp 1 -1 79" || exit 1
