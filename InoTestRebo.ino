int sunLightSensor = 7;

int mother_BMR = 8;

int motherEyeMuscles = 9;

int babyEyeMuscles = 10;

int babyEyelidMuscle = 11;


int babyBedMotor = 12;

void setup() {

  Serial.begin(9600);
  
  
  pinMode(sunLightSensor, INPUT_PULLUP);
  
  pinMode(mother_BMR, INPUT_PULLUP);
  
  pinMode(motherEyeMuscles, INPUT_PULLUP);
  
  pinMode(babyEyeMuscles, INPUT_PULLUP);
  
  pinMode(babyEyelidMuscle, INPUT_PULLUP);


  pinMode(babyBedMotor, OUTPUT);

}
void loop() {

  int day_status = digitalRead(sunLightSensor);

  int MOTHER_BMR = digitalRead(mother_BMR);

  int MotherEyeMuscles = digitalRead(motherEyeMuscles);

  int BabyEyeMuscles = digitalRead(babyEyeMuscles);

  int Baby_Eyelid = digitalRead(babyEyelidMuscle);

  if (day_status == 0 && MOTHER_BMR == 0) {

    Serial.print("Night-Time, Mother want to sleep ");

    if (MotherEyeMuscles == 0 && BabyEyeMuscles == 0) {

      Serial.print(" uh, eye contact triggered! ");

      shaking_baby(true);

      delay(900000);

      shaking_baby(false);

      if (Baby_Eyelid == 0) {

        shaking_baby(false);

        Serial.print("Yes, Baby slept so mother will going to sleep 😴 ");

      } else {

        shaking_baby(true);

        Serial.print("uh, baby didn't fall to sleep");

      }

    } else {

      Serial.print(" WAW, eye contact NOT triggered! ");

      shaking_baby(true);

      delay(180000);

      shaking_baby(false);

      if (Baby_Eyelid == 0) {

        shaking_baby(false);

        Serial.print("Yes, Baby slept so mother will going to sleep 😴 ");

      } else {

        shaking_baby(true);

        Serial.print("uh, baby didn't fall to sleep");

      }
    }

  } else {

    shaking_baby(false);

    Serial.print("Morning-Time, Mother don't want to sleep! ");
  }
}

void shaking_baby( boolean sleep ) {

  if (sleep == true) {

    digitalWrite( babyBedMotor, HIGH);

  } else {

    digitalWrite( babyBedMotor, LOW);

  }
}