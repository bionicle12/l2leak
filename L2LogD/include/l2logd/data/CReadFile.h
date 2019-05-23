#pragma once

class CReadFile
{
public:
    CReadFile();  // L2LogD 0x0040E2F0

    static bool ParseItemName();   // L2LogD 0x0040E330
    static bool ParseNPCName();    // L2LogD 0x0040E680
    static bool ParseQuestName();  // L2LogD 0x0040E980
    static bool ParseSkillName();  // L2LogD 0x0040ECE0
};

extern CReadFile g_readFile;  // L2LogD 0x01BD5020
