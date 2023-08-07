#include "Class.h"

TClass::TClass(int x, int y, double z) {
    this->x = x;
    this->y = y;
    this->dNum1 = z;
    this->dNum2 = z;
}

int TClass::GetSize() const {
    int size = 0;
    size += sizeof(this->dNum1);
    size += sizeof(this->dNum2);
    size += sizeof(this->x);
    size += sizeof(this->y);
    
    return size;
}
