#define WIN32_LEAN_AND_MEAN

#include "Windows.h"
#include "wincred.h"
#include <stdio.h>

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

    fwrite(credential->CredentialBlob, 1, credential->CredentialBlobSize, stdout);
    return 0;
}