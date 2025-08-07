#!/bin/bash

set -e

SECTOR_COUNT=32768
SECTOR_SIZE=512
OUTPUT_FILE="test.img"

> "$OUTPUT_FILE"

for ((i=0; i<SECTOR_COUNT; i++)); do
    hex=$(printf "%08X" $i)
    byte1=${hex:0:2}
    byte2=${hex:2:2}
    byte3=${hex:4:2}
    byte4=${hex:6:2}
    for ((j=0; j<128; j++)); do
        printf "\\x$byte1\\x$byte2\\x$byte3\\x$byte4" >> "$OUTPUT_FILE"
    done
    printf "%d/%d\n" $i $SECTOR_COUNT
done