#!/bin/bash

# Define the message to spam
MESSAGE = "This is a spam message"

count=1

while true
do
    if [ $count == $((1024 - $($MESSAGE | wc -c))) ]
    then
        count=1
    fi
    current_message="$MESSAGE$(printf '%*s' "$count" | tr ' ' '!')"
    echo "$current_message" | ncat -u 127.0.0.1 4242
    count=$((count + 1))
    echo "message sent"
done
