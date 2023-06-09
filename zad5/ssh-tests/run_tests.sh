#!/bin/bash
source config.sh

scp -i $SSH_KEY -P $PORT -r ../tests root@localhost:/
ssh -i $SSH_KEY -p $PORT root@localhost "cd /tests && make all"

if [ $? -ne 0 ]
then
    echo "Compilation failed"
    exit 1
fi

# for every .sh file with prefix test in this directory run it and check return code
# count the successes and failures

success=0
failures=0
for file in test*.sh
do
    echo "============ running $file ============"
    ./$file
    if [ $? -eq 0 ]
    then # add colors
        echo -e "${GREEN}Success${NC}"
        ((success++))
    else
        echo -e "${RED}Failure${NC}"
        ((failures++))
    fi
done

echo "============ Summary ============"
echo -e "${GREEN}Successes: $success ${NC}"
echo -e "${RED}Failures: $failures ${NC}"
