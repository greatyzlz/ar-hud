/*
 * @Copyright: Hascovison Corporation
 * @Author: zhangqh
 * @Date: 2022-04-24 15:25:05
 * @LastEditors: qinghongz@hascovision.com
 * @LastEditTime: 2022-04-24 16:08:41
 * @Description: 
 */

#ifndef HVTYPES_H
#define HVTYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string>

typedef int32_t         hvInt;
typedef uint32_t        hvuInt;
typedef int16_t         hvInt16;
typedef uint16_t        hvuInt16;
typedef int8_t          hvInt8;
typedef uint8_t         hvuInt8;
typedef bool            hvBool;
typedef uint8_t         hvByte;
typedef char            hvChar;
typedef unsigned char   hvuChar;

typedef std::string     hvString;

typedef enum
{
    ERR = -1,
    OK
} hvRtVal;

#endif //HVTYPES_H

