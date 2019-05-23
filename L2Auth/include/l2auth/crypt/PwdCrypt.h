#pragma once

class PwdCrypt
{
public:
    // Hash
    static void EncPwdL2(char* password);     // L2AuthD 0x0043AB0C
    static void EncPwdShalo(char* password);  // L2AuthD 0x0043AA2B
    static void EncPwdDev(char* password);    // L2AuthD 0x0043ABED
};
