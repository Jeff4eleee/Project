#ifndef Point_h
#define Point_h

#include "Arduino.h"

class Point {
    public:
        Point(int _x, int _y);

        int x, y;
        
        void print();
};

#endif
