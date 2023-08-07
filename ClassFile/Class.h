#pragma once
class TClass {
public:
    TClass() = default;
    TClass(int x, int y, double z);
    int GetSize() const;
    int x, y;
    double dNum1, dNum2;
};

