#!/bin/bash

# The specific valgrind command to run
COMMAND="valgrind --vgdb-error=0 --vgdb=full bin/linux/debug/executable"

# Detect the terminal and open a new window with valgrind command
if command -v wt.exe >/dev/null 2>&1; then                  # WSL
    wt.exe bash -c "$COMMAND && exec bash"
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