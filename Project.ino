class Point {
  public:
    int x, y;
    
    Point(int _x, int _y)  {
      x = _x;
      y = _y;
    }

    void print() {
      Serial.print("{x: ");
      Serial.print(x);
      Serial.print(", y: ");
      Serial.print(y);
      Serial.print(" }");
    }
};

class AABB {
  public:
    Point center, size;

    AABB(int x, int y, int w, int h) : center(x, y), size(w, h) {}

    static boolean collides(AABB a, AABB b) {
      if (abs(a.center.x - b.center.x) < a.size.x + b.size.x) {
        if (abs(a.center.y - b.center.y) < a.size.y + b.size.y) {
          return true;
        }
      }

      return false;
    }

    void print()  {
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
};

// PING STUFF
// VCC  -> +5V
const int trigPin = 2; // TRIG -> pin 2
const int echoPin = 3; // ECHO -> pin 3
// GND  -> ground

// MOTOR STUFF
int E1 = 6; //motor 1 speed
int E2 = 5; //motor 2 speed
int M1 = 8; //motor 1 direction
int M2 = 7; //motor 2 direction

const int maxDist = 15; // max distance in centimeters resulting in a collision
const int minDist = 0; // min distance in centimeters resulting in a collision

const char leftSpeed = 255;
const char rightSpeed = 255;

const boolean debug = true;

void setup() {
  pinMode(13, OUTPUT);
  int i;
  for (i = 5; i <= 8; i++)
    pinMode(i, OUTPUT);

  Serial.begin(9600);

  if (debug) {
    Serial.println("testing AABB...");
    AABB testAABB(0, 0, 5, 5);
    testAABB.print();

    AABB testAABB2(1, 1, 5, 5);
    testAABB2.print();

    Serial.println(AABB::collides(testAABB, testAABB2));

    Serial.println("testing AABB complete");

    Serial.println("testing movement...");
    // TEST MOVEMENT
    forward();
    delay(2000);

    reverse();
    delay(2000);

    right();
    delay(2000);

    left();
    delay(2000);

    Serial.println("testing Movement complete");
  }

  Serial.println("start");
}

void loop() {
  digitalWrite(13, HIGH);
  forward();

  long cm = ping();

  if (cm >= minDist && cm <= maxDist) {
    onCollide(cm);
  }

  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}

long ping() {
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, cm;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  return cm;
}

void forward() {
  analogWrite (E1, leftSpeed);
  digitalWrite(M1, LOW);
  analogWrite (E2, rightSpeed);
  digitalWrite(M2, LOW);
}

void stop() {
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
}

void reverse() {
  analogWrite (E1, leftSpeed);
  digitalWrite(M1, HIGH);
  analogWrite (E2, rightSpeed);
  digitalWrite(M2, HIGH);
}

void left() {
  analogWrite (E1, leftSpeed);
  digitalWrite(M1, HIGH);
  analogWrite (E2, rightSpeed);
  digitalWrite(M2, LOW);
}

void right() {
  analogWrite (E1, leftSpeed);
  digitalWrite(M1, LOW);
  analogWrite (E2, rightSpeed);
  digitalWrite(M2, HIGH);
}

void onCollide(long cm) {
  Serial.print("collide at ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  Serial.println("calculation collision...");

  reverse();

  delay(500);

  right();

  delay(1000);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
