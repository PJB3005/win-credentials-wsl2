cl /Fecred_debug.exe /nologo /O2 /W3 cred.c Advapi32.lib kernel32.lib /utf-8 /GS- /MD /link /subsystem:console

cl /Fecred.exe /nologo /O2 /W3 cred.c Advapi32.lib kernel32.lib /utf-8 /GS- /MD /link /incremental:no /opt:icf /opt:ref /subsystem:console
cl /Fecred_static.exe /nologo /O2 /W3 cred.c Advapi32.lib kernel32.lib /utf-8 /GS- /MT /link /incremental:no /opt:icf /opt:ref /subsystem:console
