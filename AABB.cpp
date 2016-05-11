#include "Arduino.h"
#include "Point.h"
#include "AABB.h"

AABB::AABB(int x, int y, int w, int h) : center(x, y), size(w, h) {}

void AABB::print() {
    Serial.print("{ x: ");
    Serial.print(center.x);
    Serial.print(", y: ");
    Serial.print(center.y);
    Serial.print(", w: ");
    Serial.print(size.x);
    Serial.print(", h: ");
    Serial.print(size.y);
    Serial.println(" }");	
}

boolean AABB::collides(AABB a, AABB b) {
    if (abs(a.center.x - b.center.x) < a.size.x + b.size.x) {
        if (abs(a.center.y - b.center.y) < a.size.y + b.size.y) {
            return true;
        }
    }

    return false;
}
