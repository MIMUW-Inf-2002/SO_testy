#!/bin/bash
source config.sh

FOO_PASSWD=mimuwrules
FOO_PASSWD_CRYPT=saFKLiF4jRXiE

# z niewiadomych powodów dodanie użytkownika w jednym poleceniu ssh nie działa... (ale przez konsolę ssh działa)
# ssh -i $SSH_KEY -p $PORT root@localhost "user add -m -g operator -p $FOO_PASSWD_CRYPT foo\r"

echo To add user type inside minix: 
echo user add -m -g users -p $FOO_PASSWD_CRYPT foo

read -n 1 -s -r -p "Press any key to continue..."

echo After adding user, add ssh keys to both users:
echo For root, password is 'root'
ssh-copy-id -p $PORT root@localhost
echo For foo, password is \'$FOO_PASSWD\'
ssh-copy-id -p $PORT foo@localhost
