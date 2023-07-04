#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define ERR(...) {fprintf(stderr, "\033[31m[!]\033[0m"); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#define WARN(...) {printf("\033[33m[*]\033[0m"); printf(__VA_ARGS__); printf("\n");}
#define LOG(...) {printf ("\033[32m[+]\033[0m"); printf(__VA_ARGS__); printf("\n");}

#define OK true
#define FAILED false;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef unsigned char ubyte;

#endif // COMMON_H
