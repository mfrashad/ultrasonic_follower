#define trigPin1 A3
#define echoPin1 A4
#define trigPin2 A6
#define echoPin2 A7
#define trigPin3 A0
#define echoPin3 A1

#define left_dir1 24
#define left_dir2 25
#define left_pwm 8

#define right_dir1 26
#define right_dir2 27
#define right_pwm 7

#define LEFT 0
#define FRONT 1
#define RIGHT 2

#define NUM_SENSORS 3

 
long duration, distance,closest_distance, right_sensor, left_sensor, front_sensor;

long sensor[NUM_SENSORS];

int position, error, base_speed;
 
void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(left_dir1, OUTPUT);
  pinMode(left_dir2, OUTPUT);
  pinMode(left_pwm, OUTPUT);
  pinMode(right_dir1, OUTPUT);
  pinMode(right_dir2, OUTPUT);
  pinMode(right_pwm, OUTPUT);
}
 
void loop() {
  readSensors();
 
  Serial.print(sensor[LEFT]);
  Serial.print(" - ");
  Serial.print(sensor[FRONT]);
  Serial.print(" - ");
  Serial.println(sensor[RIGHT]);

}

void forward(int left_speed, int right_speed){
  setDirForward();
  setLeftSpeed(left_speed);
  setRightSpeed(right_speed);
}

void setDirForward(){
  setLeftDir(1);
  setRightDir(0);
}

void setDir(int dir){
  setLeftDir(dir);
  setRightDir(dir);
}

void setLeftDir(int dir){
  digitalWrite(left_dir1, dir);
  digitalWrite(left_dir2, !dir);
}
void setRightDir(int dir){
  digitalWrite(right_dir1, dir);
  digitalWrite(right_dir2, !dir);
}

void setLeftSpeed(int speed){
  digitalWrite(left_pwm, speed);
}
void setRightSpeed(int speed){
  digitalWrite(right_pwm, speed);
}

void setSpeed(int speed){
  setLeftSpeed(speed);
  setRightSpeed(speed);
}


void readSensors(){
  sensor[LEFT] = readSensor(trigPin1, echoPin1);
  sensor[FRONT] = readSensor(trigPin2, echoPin2);
  sensor[RIGHT] = readSensor(trigPin3, echoPin3);

  int close_sensor_count = 0;
  int sensor_sum = 0;
  for(int i=0; i<NUM_SENSORS; i++){
    close_sensor_count += isSensorClose(i);
    sensor_sum += i * isSensorClose(i);
  }

  // Position range from 0-20
  position = sensor_sum * 10 / close_sensor_count;
  error = position - 10;
}

void calculateBaseSpeed(){
  closest_distance = 100;
  for(int i=0; i<NUM_SENSORS; i++){
    if(sensor[i] < closest_distance) closest_distance = sensor[i];
  }
  base_speed = 30 + closest_distance;
}

void calculateSpeedDifference(){
  
}

int isSensorClose(int sensor_index){
  return sensor[sensor_index] < 20;
}
 
long readSensor(int trigPin,int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  distance = (duration/2) / 29.1;
  return distance;
}
