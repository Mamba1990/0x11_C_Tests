#!/bin/bash

max_pid=$(cat /proc/sys/kernel/pid_max)
echo "Maximum Process ID: $max_pid"
