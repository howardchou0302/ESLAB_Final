#include "rfid.h"

RFID_Reader::RFID_Reader()
{
    _mfrc522 = 0;
    _id = 0;
}

RFID_Reader::RFID_Reader(MFRC522 *mfrc522)
{
    _mfrc522 = mfrc522;
    _mfrc522->PCD_Init();
    _id = new int[10];
}

bool RFID_Reader::read()
{
    if ( ! _mfrc522->PICC_IsNewCardPresent()) return false;
    if ( ! _mfrc522->PICC_ReadCardSerial()) return false;
    _idSize = _mfrc522->uid.size;
    for(int i = 0; i < _idSize; ++i) _id[i] = _mfrc522->uid.uidByte[i];
    _mfrc522->PICC_HaltA();
    return true;
}