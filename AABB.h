#ifndef AABB_h
#define AABB_h

#include "Arduino.h"
#include "Point.h"

class AABB {
    public:
        AABB(int x, int y, int w, int h);

        Point center, size;
        
        static boolean collides(AABB a, AABB b);
        
        void print();
};

#endif
