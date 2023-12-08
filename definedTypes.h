#pragma once

typedef struct {
    unsigned int sequence;
    unsigned char format;
    unsigned char flags;
    unsigned int length;
    unsigned int childCount;
    unsigned int valueOffset;
    void *value;
} bejTuple;

typedef struct{
    unsigned char format;
    unsigned char flags;
    unsigned short sequence;
    unsigned short childPointerOffset;
    unsigned short childCount;
    unsigned char nameLength;
    unsigned short nameOffset;
}entryData;