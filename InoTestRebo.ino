/**
 * @author Hamza Zhour
 * @brief this is an arduino test project
 *
 */
#define sunLightSensor 7    // define board pin number as a variable.
#define mother_BMR 8        // define board pin number as a variable.
#define motherEyeMuscles 9  // define board pin number as a variable.
#define babyEyeMuscles 10   // define board pin number as a variable.
#define babyEyelidMuscle 11 // define board pin number as a variable.

#define babyBedMotor 12 // define board pin number as a variable.

void setup()
{

   Serial.begin(9600);

   pinMode(sunLightSensor, INPUT_PULLUP);   // Assign board pin port as a digital 5v+ voltage input.
   pinMode(mother_BMR, INPUT_PULLUP);       // Assign board pin port as a digital 5v+ voltage input.
   pinMode(motherEyeMuscles, INPUT_PULLUP); // Assign board pin port as a digital 5v+ voltage input.
   pinMode(babyEyeMuscles, INPUT_PULLUP);   // Assign board pin port as a digital 5v+ voltage input.
   pinMode(babyEyelidMuscle, INPUT_PULLUP); // Assign board pin port as a digital 5v+ voltage input.

   pinMode(babyBedMotor, OUTPUT); // Assign board pin port as a digital 5v+ voltage output.
}
void loop()
{

   int day_status = digitalRead(sunLightSensor);         // Read Day-Time which 1 == MORNING and 0 == NIGHT.
   int MOTHER_BMR = digitalRead(mother_BMR);             // Read Mother Basal-Metabolic-Rate which 0 == LOW BMR and 1 == NORMAL/HIGH.
   int MotherEyeMuscles = digitalRead(motherEyeMuscles); // Read Mother-Eye-Muscles which 0 == Stopped at certain position and 1 == In action.
   int BabyEyeMuscles = digitalRead(babyEyeMuscles);     // Read Baby-Eye-Muscles which 0 == Stopped at certain position and 1 == In action.
   int Baby_Eyelid = digitalRead(babyEyelidMuscle);      // Detect Baby-Eyelid-Closure which 0 == CLOSED and 1 == OPENED.

   if (day_status == 0 && MOTHER_BMR == 0) // Check if mother want to sleep and the day-time is night.
   {

      Serial.print("Night-Time, Mother want to sleep ");

      if (MotherEyeMuscles == 0 && BabyEyeMuscles == 0) // Check if mother & baby eyes are in contact or not.
      {
         Serial.print(" uh, eye contact triggered! ");
         shaking_baby(true);  // Run Shaking baby bed function.
         delay(900000);       // Wait 15 min until baby sleep, 15 min needed due to eye contact triggered.
         shaking_baby(false); // Stop Shaking baby bed function.

         if (Baby_Eyelid == 0) // Check if baby-Eyelids are closed which 0 == closed.
         {
            shaking_baby(false); // Stop Shaking baby bed function.
            Serial.print("Yes, Baby slept so mother will going to sleep 😴 ");
         }
         else
         {
            shaking_baby(true); // Run Shaking baby bed function.
            Serial.print("uh, baby didn't fall to sleep");
         }
      }
      else
      {
         Serial.print(" WAW, eye contact NOT triggered! ");
         shaking_baby(true);  // Run Shaking baby bed function.
         delay(180000);       // Wait 3 min until baby sleep, 3 min needed due to eye contact not triggered.
         shaking_baby(false); // Stop Shaking baby bed function.

         if (Baby_Eyelid == 0) // Check if baby-Eyelids are closed which 0 == closed.
         {
            shaking_baby(false); // Stop Shaking baby bed function.
            Serial.print("Yes, Baby slept so mother will going to sleep 😴 ");
         }
         else
         {
            shaking_baby(true); // Run Shaking baby bed function.
            Serial.print("uh, baby didn't fall to sleep");
         }
      }
   }
   else
   {
      shaking_baby(false); // Stop Shaking baby bed function.... Defult value.
      Serial.print("Morning-Time, Mother don't want to sleep! ");
   }
}

void shaking_baby(boolean sleep)
{
   if (sleep == true)
   {
      digitalWrite(babyBedMotor, HIGH); // Run motor.
   }
   else
   {
      digitalWrite(babyBedMotor, LOW); // Stop motor.
   }
}