#pragma once

enum PlayFail
{
    PLAY_FAIL_NO_ERROR = 0x0,
    PLAY_FAIL_SOME_ERROR = 0x6,
    PLAY_ACCOUNT_IN_USE = 0x7,
    PLAY_FAIL_GS_ERROR = 0x8,
    PLAY_FAIL_SYSTEM_ERROR = 0x9,
    PLAY_FAIL_WRONG_ACC_NAME = 0xA,
    PLAY_FAIL_ALREADY_LOGGED = 0xE,
};
