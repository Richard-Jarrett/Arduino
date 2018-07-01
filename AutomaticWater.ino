  // Pin definition for Solenoid
int SOLENOID = 2;
  // Delays required to give 1 second
int DelayPerSecond = 1000;

//##########################################
  // Options to configure watering!

  // Water on time in seconds (3600 = 1 hour)
long RunSeconds = 10;  
  // Period cycle time in seconds (86400 = 24 hours)
long PeriodSeconds = 240;
//##########################################

// the setup routine runs once when you press reset:
void setup() {
    // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
    // initialize Solenoid pin to being output
  pinMode(SOLENOID, OUTPUT);
    // initialize LED_BUILTIN pin to being output
  pinMode(LED_BUILTIN, OUTPUT);

    // Set on start states
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(SOLENOID, LOW);

    // Write settings to console
  Serial.print("DelayPerSecond    = ");
  Serial.println(DelayPerSecond);
  Serial.print("Water run time    = ");
  Serial.println(RunSeconds);
  Serial.print("Cycle Period time = ");
  Serial.println(PeriodSeconds);
}

// the loop routine runs over and over again forever:
void loop() {

  for(long CountSeconds; CountSeconds < PeriodSeconds; CountSeconds++)
  {
    Serial.println(CountSeconds);
    if(CountSeconds <= RunSeconds)
    {
      Serial.println("Solenoid On");
      digitalWrite(SOLENOID, HIGH);
    }
    else
    {
      Serial.println("Solenoid OFF");
      digitalWrite(SOLENOID, LOW);
    }
    RunSecond();
  }
  Serial.println("########## End Of Day ##########");
}

void RunSecond()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(DelayPerSecond / 10);
  digitalWrite(LED_BUILTIN, LOW);
  delay((DelayPerSecond / 10)*9);
  Serial.println("tick");
}

