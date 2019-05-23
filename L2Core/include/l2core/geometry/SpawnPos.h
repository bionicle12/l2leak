#pragma once

struct SpawnPos
{
    SpawnPos(int xx, int yy, int zz, int dir, int ch);  // L2NPC 0x00486A00

    int locX;
    int locY;
    int locZ;
    int direction;
    int chance;
};
