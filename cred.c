#define WIN32_LEAN_AND_MEAN

#include "Windows.h"
#include "wincred.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Must specify credentials key!\n");
        return 1;
    }

    LPCSTR key = argv[1];
#if DEBUG
    fprintf(stderr, "Key: %s\n", key);
#endif

    PCREDENTIALA credential;
    if (!CredReadA(key, CRED_TYPE_GENERIC, 0, &credential)) {
        HRESULT err = GetLastError();
        char errBuf[512];
        DWORD errChars = FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            err,
            0,
            errBuf,
            sizeof(errBuf),
            NULL);

        if (errChars == 0) {
            fprintf(stderr, "Failed to print previous error!\n");
            return 1;
        }

        fprintf(stderr, "Failed to get credential: %s", errBuf);
        return 1;
    }

    int length = WideCharToMultiByte(CP_UTF8, 0, (LPWCH) credential->CredentialBlob, credential->CredentialBlobSize / 2, NULL, 0, NULL, NULL);
    char* buf = malloc(length);
    WideCharToMultiByte(CP_UTF8, 0, (LPWCH) credential->CredentialBlob, credential->CredentialBlobSize / 2, buf, length, NULL, NULL);

    fwrite(buf, 1, length, stdout);
    fwrite("\n", 1, 1, stdout);
    fflush(stdout);
    return 0;
}
