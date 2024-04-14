#!/bin/sh
get_curvol() {
    awk '/LineOut/ {if (!printed) {gsub(",", "", $8); print $8; printed=1}}' /proc/mi_modules/mi_ao/mi_ao0
}

set_snd_level() {
    local target_vol="$1"
    local current_vol
    local start_time
    local elapsed_time

    start_time=$(date +%s)
    while [ ! -e /proc/mi_modules/mi_ao/mi_ao0 ]; do
        sleep 0.2
        elapsed_time=$(( $(date +%s) - start_time ))
        if [ "$elapsed_time" -ge 30 ]; then
            echo "Timed out waiting for /proc/mi_modules/mi_ao/mi_ao0"
            return 1
        fi
    done

    start_time=$(date +%s)
    while true; do
        echo "set_ao_volume 0 ${target_vol}dB" > /proc/mi_modules/mi_ao/mi_ao0
        echo "set_ao_volume 1 ${target_vol}dB" > /proc/mi_modules/mi_ao/mi_ao0
        current_vol=$(get_curvol)

        if [ "$current_vol" = "$target_vol" ]; then
            echo "Volume set to ${current_vol}dB"
            return 0
        fi

        elapsed_time=$(( $(date +%s) - start_time ))
        if [ "$elapsed_time" -ge 30 ]; then
            echo "Timed out trying to set volume"
            return 1
        fi

        sleep 0.2
    done
}

progdir=`dirname "$0"`
cd $progdir
export LD_LIBRARY_PATH=$progdir/libs:$LD_LIBRARY_PATH

curvol=$(get_curvol) # grab current volume

if [ -f /mnt/SDCARD/.tmp_update/script/stop_audioserver.sh ]; then
    /mnt/SDCARD/.tmp_update/script/stop_audioserver.sh
else
    killall audioserver
    killall audioserver.mod
fi

CUST_CPUCLOCK=1

sv=`cat /proc/sys/vm/swappiness`

# 60 by default
echo 10 > /proc/sys/vm/swappiness

if [ "$CUST_CPUCLOCK" == "1" ]; then
    echo "set customized cpuspeed"
    cpuclock 1500
fi

set_snd_level "${curvol}" &

./Zelda

if [ "$CUST_CPUCLOCK" == "1" ]; then
    echo "set customized cpuspeed"
    cpuclock 1200
fi

echo $sv > /proc/sys/vm/swappiness
sync
