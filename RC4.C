#include <stdio.h>
#include <string.h>

void swap(unsigned char *a, unsigned char *b)
{
    unsigned char t = *a;
    *a = *b;
    *b = t;
}

void RC4(unsigned char *p, int plen, unsigned char *key, int klen,
         unsigned char *c)
{
    unsigned char S[256];
    int i, j = 0, k, t;

    /* Initialize S */
    for (i = 0; i < 256; i++)
        S[i] = i;

    /* KSA */
    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % klen]) % 256;
        swap(&S[i], &S[j]);
    }

    /* PRGA */
    i = j = 0;

    for (k = 0; k < plen; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(&S[i], &S[j]);

        t = (S[i] + S[j]) % 256;
        c[k] = p[k] ^ S[t];
    }
}

int main()
{
    unsigned char plaintext[500];
    unsigned char key[100];
    unsigned char ciphertext[500];

    int i, plen, klen;

    printf("Enter plaintext: ");
    scanf("%499s", plaintext);

    printf("Enter key/name: ");
    scanf("%99s", key);

    plen = strlen((char *)plaintext);
    klen = strlen((char *)key);

    RC4(plaintext, plen, key, klen, ciphertext);

    printf("\nPlaintext : %s", plaintext);
    printf("\nKey       : %s", key);

    printf("\n\nRC4 Ciphertext (Hex):\n");

    for (i = 0; i < plen; i++)
        printf("%02X", ciphertext[i]);

    printf("\n");

    return 0;
}