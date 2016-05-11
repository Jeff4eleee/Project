#include "Arduino.h"
#include "Point.h"

Point::Point(int _x, int _y) {
    x = _x;
    y = _y;
}

void Point::print() {
    Serial.print("{x: ");
    Serial.print(x);
    Serial.print(", y: ");
    Serial.print(y);
    Serial.print(" }");
}
