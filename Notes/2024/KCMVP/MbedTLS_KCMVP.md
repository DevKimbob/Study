MbedTLS w/ KCMVP  <!-- omit in toc -->
====

**Table of Contents**
- [1. Reference Source Code Comparison](#1-reference-source-code-comparison)
  - [include/KDN/](#includekdn)
    - [KDN\_LIB.h](#kdn_libh)
  - [include/mbedtls/](#includembedtls)
    - [aria.c](#ariac)
    - [config.h](#configh)
    - [ctr\_drbg.h](#ctr_drbgh)
    - [ecdh.h](#ecdhh)
    - [ecdsa.h](#ecdsah)
    - [sha256.h](#sha256h)
  - [library/](#library)
    - [aria.c](#ariac-1)
    - [ctr\_drbg.c](#ctr_drbgc)
    - [ecdh.c](#ecdhc)
    - [ecdsa.c](#ecdsac)
    - [sha256.c](#sha256c)
  - [programs/](#programs)
    - [Makefile](#makefile)
  - [tests/](#tests)
    - [Makefile](#makefile-1)


# 1. Reference Source Code Comparison
MbedTLS version 2.16.5

## include/KDN/
### KDN_LIB.h
> copy header file

## include/mbedtls/
### aria.c
```c
// 46
#include "KDN/KDN_LIB.h"

// 80
typedef struct mbedtls_aria_context
{
    ...
    uint8 kcmvp_key[16];
    int kcmvp;
}
mbedtls_aria_context;
```

### config.h
```c
// 2083
#define MBEDTLS_ARIA_C
```

### ctr_drbg.h
```c
// 76
#include "KDN/KDN_LIB.h"
```

### ecdh.h
```c
// 47
#include "KDN/KDN_LIB.h"
```

### ecdsa.h
```c
// 46
#include "KDN/KDN_LIB.h"
```

### sha256.h
```c
// 41
#include "KDN/KDN_LIB.h"
```

## library/
### aria.c
```c
// 447
int mbedtls_aria_setkey_enc(...) {
    // 487
    ctx->kcmvp = 0;
    if (ctx->nr == 12) {
        for (int i = 0; i < 16; i++) ctx->kcmvp_key[i] = key[i];
        ctx->kcmvp = 1;
    }
}

// 521
int mbedtls_aria_setkey_des(...) {
    // 532
    if (ctx->nr == 12) {
        for (int i = 0; i < 16; i++) ctx->kcmvp_key[i] = key[i];
        ctx->kcmvp = 2;
    }
}
```
```c
// 562
int mbedtls_aria_crypt_ecb(...) {
    // 580
    if (ctx->kcmvp == 1) {
        KDN_BC_Encrypt(...);
    }
    else if (ctx->kcmvp == 2) {
        KDN_BC_Decrypt(...);
    }
    else {
        ...
    }
}
```
```c
// 666
int mbedtls_aria_crypt_cbc(...) {
    // 686
    if (mode == MBEDTLS_ARIA_DECRYPT) {
        if (ctx->kcmvp == 2) {
            KDN_BC_Decrypt(...);
        }
    } else {
        if (ctx->kcmvp == 1) {
            KDN_BC_Encrypt(...);
        }
    }
}
```
```c
// 752
int mbectls_aria_crypt_cfb128(...) {
    // 779
    ctx->kcmvp = 0;
}
```
```c
// 819
int mbedtls_aria_crypt_ctr(...) {
    // 845
    if (ctx->kcmvp == 1 && n == 0) {
        KDN_BC_Encrypt(...);
    } else if (ctx->kcmvp == 2 && n == 0) {
        KDN_BC_Decrypt(...);
    } else {
        ...
    }
}
```

### ctr_drbg.c
```c
// 520
int mbedtls_ctr_drbg_random(...) {
    // 531
    ret = KDN_Gen_RandNumber(...);
}
```

### ecdh.c
```c
// 96
int mbedtls_ecdh_gen_public(...) {
    if (grp->id == MBEDTLS_ECP_DP_SECP256R1) {
        KDN_KT_ECDH(...);
    }
}

// 191
int mbedtls_ecdh_compute_shared(...) {
    if (grp->id == MBEDTLS_ECP_DP_SECP256R1) {
        KDN_SK_ECDH(...);
    }
}
```

### ecdsa.c
```c
// 389
void KDN_Ascii_to_Hex(...) {...}  // new function

// 426
int mbedtls_ecdsa_sign(...) {
    if (grp->id == MBEDTLS_ECP_DP_SECP256R1) {
        KDN_Ascii_to_Hex(...);
        KDN_Sign_ECDSA(...);
    }
}

// 761
int mbedtls_ecdsa_verify(...) {
    if (grp->id == MBEDTLS_ECP_DP_SECP256R1) {
        KDN_Ascii_to_Hex(...);
        KDN_Verify_ECDSA(...);
    }
}

// 1002
int mbedtls_ecdsa_genkey(...) {
    if (grp == MBEDTLS_ECP_DP_SECP256R1) {
        KDN_Keygen_ECDSA(...);
    }
}
```

### sha256.c
```c
// 414
int mbedtls_sha256_ret(...) {
    if (ctx.is224 == 1) {
        ...
    } else {
        KDN_Digest(...);
    }
}
```

## programs/
### Makefile
```makefile
# 8
LDFLAGS ?= -lepowercrypto
```

## tests/
### Makefile
```makefile
# 7
LDFLAGS ?= -lepowercrypto
```