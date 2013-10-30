int DEBUG                         = 1;   // Set to 1 for debug Serial info
int DELAY                         = 20;  // Delay for every loop
int LED_PIN                       = 0;   // Debug LED; set to 0 if you've used all your ports
const byte NUMBER_OF_PINS         = 14;  // Total number of pins used
int inputStates[NUMBER_OF_PINS];         // Inputstates holder array
boolean btn_pressed = false;             // Button pressed state

int inputPins[NUMBER_OF_PINS]   = {0,1,2,3,4,5,6,7,8,9,10,11,12,13}; // Pinmap
uint8_t inputValuesMapped[]     = {'z','y','t','o','u','d','v','k','l','j','i','q','p','s'}; // Corresponding values

void setup()
{

  Keyboard.begin();
  
  for(int i = 0; i < NUMBER_OF_PINS; i++){
     pinMode(inputPins[i], INPUT);
     digitalWrite(inputPins[i], HIGH);
     inputStates[0] = 0;
  }
  
  if(LED_PIN!=0) {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);    
  }
  
  if(DEBUG) Serial.begin(9600);
}

void loop()
{
  btn_pressed = false;
  for(int i = 0; i < NUMBER_OF_PINS; i++)
  {
    int button_pressed = !digitalRead(inputPins[i]); 
    if(button_pressed)
    {
      if(inputStates[i] != 1)
      {
        Keyboard.press(inputValuesMapped[i]);
        inputStates[i] = 1;
        if(DEBUG) Serial.println("KEY PRESSED: "+inputValuesMapped[i]);
        if(LED_PIN!=0) digitalWrite(LED_PIN, HIGH);
      }
    }
    else
    {
      if(inputStates[i] == 1) Keyboard.release(inputValuesMapped[i]); 
      inputStates[i] = 0;
      if(LED_PIN!=0) digitalWrite(LED_PIN, LOW);
    }
  }
  
  for(int i = 0; i < NUMBER_OF_PINS; i++)
  {
    if(inputStates[i])
    {
      if(LED_PIN!=0) digitalWrite(LED_PIN, HIGH);
      btn_pressed = true;
    }else
    {
      if(!btn_pressed)
      {
        if(LED_PIN!=0) digitalWrite(LED_PIN, LOW);
      }
    }
  }
  
  delay(DELAY);
}
