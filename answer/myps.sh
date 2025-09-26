#!/bin/bash
# myps.sh - print a single process line with full fields or "no process found for {PID}"

if [ $# -ne 1 ]; then
  echo "Usage: $0 PID"
  exit 1
fi

PID="$1"

# use ps with explicit column order so output is predictable
# we don't print header unless we find a match
matches=$(ps -eo f=,s=,uid=,pid=,ppid=,c=,pri=,ni=,addr=,sz=,wchan=,tty=,time=,cmd= | awk -v pid="$PID" '$4==pid {print}')

if [ -z "$matches" ]; then
  echo "no process found for $PID"
  exit 0
fi

echo "F S UID PID PPID C PRI NI ADDR SZ WCHAN TTY TIME CMD"
echo "$matches"
