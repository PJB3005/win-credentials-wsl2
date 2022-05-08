# WSL2 WinCred bridge

This is a tiny bridge program to read credentials from WinCred, from WSL2. Means I can stop entering Ansible vault passwords in WSL2.

To use, put `cred.exe` anywhere accessible to Linux, and simply run it from Linux with argument being the credentials key to read.

To add or manage credentials, use Credentials Manager from Control Panel. The username entered is ignored.