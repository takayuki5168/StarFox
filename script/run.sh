SCRIPT_DIR=$(dirname $0)
OPTION=$1

if [ ${OPTION} == "-w" ]; then
    python ${SCRIPT_DIR}/../python/main.py &
    ${SCRIPT_DIR}/../build/main -w
elif [ ${OPTION} == "-v" ]; then
    ${SCRIPT_DIR}/../build/main -v
else
    ${SCRIPT_DIR}/../build/main
fi

killall python
