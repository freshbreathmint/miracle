#!/usr/bin/env python3

import sys
import configparser
import platform
import subprocess
import shutil
import os

def is_wsl():
    """Check if the script is running under WSL."""
    return 'microsoft' in platform.uname().release.lower()

def main():
    # Check if arguments are passed
    if len(sys.argv) < 2:
        print("No arguments provided. Usage: ./run_command.py <command> [arguments...]")
        sys.exit(1)

    # Read config.ini to get application name
    config = configparser.ConfigParser()
    config_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../config.ini')
    if not config.read(config_path):
        print(f"Failed to read config.ini at {config_path}.")
        sys.exit(1)

    if 'application' not in config or 'name' not in config['application']:
        print("config.ini is missing 'application' section or 'name' option.")
        sys.exit(1)

    application_name = config['application']['name']

    # Replace 'executable' in command and arguments with application name
    modified_args = [arg.replace('release/executable', f'release/{application_name}') for arg in sys.argv[1:]]
    command = ' '.join(modified_args)

    # Detect if running under WSL
    if is_wsl():
        # Check if wt.exe is available
        if shutil.which('wt.exe'):
            # Use Windows Terminal to run the command
            # The '&& exec bash' keeps the terminal open after the command executes
            wt_command = f'wt.exe bash -c "{command} && exec bash"'
            subprocess.Popen(wt_command, shell=True)
            sys.exit(0)
        else:
            print("WSL detected but wt.exe (Windows Terminal) is not available.")
            sys.exit(1)

    # Detect the terminal and open a new window
    if shutil.which('gnome-terminal'):
        terminal_cmd = ['gnome-terminal', '--', 'bash', '-c', f"{command}; exec bash"]
    elif shutil.which('konsole'):
        terminal_cmd = ['konsole', '--noclose', '-e', command]
    elif shutil.which('xfce4-terminal'):
        terminal_cmd = ['xfce4-terminal', '--hold', '-e', command]
    elif shutil.which('xterm'):
        terminal_cmd = ['xterm', '-hold', '-e', command]
    elif shutil.which('wt.exe'):
        # In case the script is not running under WSL but wt.exe is available
        wt_command = f'wt.exe bash -c "{command} && exec bash"'
        terminal_cmd = wt_command
    else:
        print("No supported terminal emulator found.")
        sys.exit(1)

    try:
        if isinstance(terminal_cmd, list):
            subprocess.Popen(terminal_cmd)
        else:
            # For wt.exe or other string commands
            subprocess.Popen(terminal_cmd, shell=True)
    except Exception as e:
        print(f"Failed to open terminal and execute command: {e}")
        sys.exit(1)

if __name__ == '__main__':
    main()