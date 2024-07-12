PQC  <!-- omit in toc -->
===

**Table of Contents**
- [PQC](#pqc)
- [IEC61850](#iec61850)
- [DNP3](#dnp3)


# PQC
CRYSTALS-KYBER
CRYSTALS-LILITHIUM

Kaist : PQC 알고리즘 등록 시도. -> KCMVP에서 사용 가능성도 존재?

# IEC61850
EVP_PKEY_base_id
: legacy. PQC하고는 현재 호환 안됨 0 반환

sslemain.c : 1992
sslecert_comn.c : 767

# DNP3
DNPSlave.c : 260 (oqs ref)

mdnpsa/sdnpsa.c : OQS_KEM_kyber_768_encaps/decaps

tmwcrypto.c : pub/priv key in struct is not used?
mdnpauth.h : 475 (used?)
sdnpauth.h : 342 (same)

sdnpsa.c : 1713
mdnpsa.c : 3891

sdnpauth.h : 64