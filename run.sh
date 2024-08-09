#!/bin/bash

# Check if arguments are passed
if [ $# -eq 0 ]; then
    echo "No argumnets provided. Usage: ./run.sh <command> [arguments...]"
    exit 1
fi

# The command to run in the new terminal window
COMMAND="$@"

# TODO: Add a flag to run natively in wt.exe so we aren't going through bash for windows executables.

# Detect the terminal and open a new window
if command -v wt.exe >/dev/null 2>&1; then                  # WSL
    wt.exe bash -c "$COMMAND"
elif command -v gnome-terminal >/dev/null 2>&1; then        # GNOME
    gnome-terminal -- bash -c "$COMMAND; exec bash"
elif command -v konsole >/dev/null 2>&1; then               # KDE
    konsole --noclose -e "$COMMAND"
elif command -v xfce4-terminal >/dev/null 2>&1; then        # XFCE
    xfce4-terminal --hold -e "$COMMAND"
elif command -v xterm >/dev/null 2>&1; then                 # xterm
    xterm -hold -e "$COMMAND"
else
    echo "No supported terminal emulator found."
    exit 1
fi