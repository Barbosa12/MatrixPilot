#ifndef _MYIPHELPERS_H_
#define _MYIPHELPERS_H_

#include "MyIpData.h"

void StringToSocket(const uint8_t s, const char * buf);
void StringToSrc(const eSource src, const char * buf);
void ArrayToSrc(const eSource src, const uint8_t* buf, const int16_t len);
void ultoaSrc(const eSource src, const uint32_t data);
void itoaSrc(const eSource src, const int16_t data);
void uitoaSrc(const eSource src, const uint16_t data);
void ltoaSrc(const eSource src, const int32_t data);
void itoaSocket(const uint8_t s, const int16_t value);
void ltoaSocket(const uint8_t s, const int32_t value);
void uitoaSocket(const uint8_t s, const uint16_t value);
void ultoaSocket(const uint8_t s, const  uint32_t value);
void ftoaSocket(const uint8_t s, const float value, const uint8_t decCount);
void itoa(int16_t value, uint8_t* Buffer);
void ltoa(int32_t value, uint8_t* Buffer);
void ToHexToSocket(const uint8_t s, const uint32_t value, const uint8_t size);
void ToHexToSrc(const eSource src, const uint32_t value, const uint8_t size);

void ByteToSocket(const uint8_t s, const uint8_t data);
void ArrayToSocket(const uint8_t s, const uint8_t* data, uint32_t len);
void ByteToSrc(const eSource src, const uint8_t data);
boolean MyIpIsConnectedSrc(const eSource src);
boolean MyIpIsConnectedSocket(const uint8_t s);
uint8_t parseCSV(const uint8_t* bufCSV, const int16_t len, int32_t* result, const uint8_t commaLimit);

int8_t MyIphex_AsciiToBinary(const uint8_t inchar);
float ReverseFloat(const float inFloat);
uint8_t ToAsciiHex4bit(const uint8_t value);
void printAircraftState(uint8_t s);


#endif // _MYIPHELPERS_H_