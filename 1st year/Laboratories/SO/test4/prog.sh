#!/bin/bash
users_file=$1
if [ ! -n "$users_file" ] || [ ! -f $users_file ]; then
        echo "Invalid file..."
        echo "Usage ./prog.sh FILE"
        exit 1
fi
while [ 0 ]; do
        read -p "Zi: " day
        read -p "Luna: " month
        let "0 <= day && day <= 31" || continue
        for user in $(cat $users_file); do
                found=$(last | grep "$user.*$month $day")
                if [ -n "$found" ]; then echo "$user a fost logat"; fi
                if [ -z "$found" ]; then echo "$user nu a fost logat"; fi
        done
done
