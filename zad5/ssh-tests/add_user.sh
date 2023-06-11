#!/bin/bash
source config.sh

echo To add user type inside minix: 
echo user add -m -g users -p $FOO_PASSWD_CRYPT foo

read -n 1 -s -r -p "Press any key to continue..."
