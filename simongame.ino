int ledArray[] = {12, 9, 5, 2};      // ledArray[0] is green, ledArray[1] is red, ledArray[2] is yellow, and ledArray[3] is blue. 
int buttonArray[] = {13, 10, 6, 3};  // buttonArray[0] is green, buttonArray[1] is red, buttonArray[2] is yellow, and buttonArray[3] is blue. 
int pinCount = 4;                    // Both ledArray and buttonArray have same pinCount --> use this for both buttons and leds.
int buzzer = 8;                      // 8 is the pin the buzzer is connected to.

/* With ledState = 0 meaning the current LED is blue, 1 meaning the current LED is green, 
 2 meaning the current LED is red and 3 meaning the current LED is yellow. */
int ledState = 0;
/* With gameState = 0 meaning the game hasn't started, 
1 meaning the user is playing, 2 meaning the user has won and 3 meaning the user has lost. */
int gameState = 0;

#define NUMBERTOWIN 3                // Number of lights you have to match to win.
int gameValues[NUMBERTOWIN];
int roundNum = 0;

unsigned long previousMillis = 0;    // Need this for pre-game state for flashing lights without delay --> if you use delay your button push to start game may not be noticed.
unsigned long interval1 = 500;       // Need this for time between blinks.

// 7 segments to represent level
int a = A5;  // For displaying segment "a"     
int b = A4;  // For displaying segment "b"      //    - a -
int c = A3;  // For displaying segment "c"      //    f   b
int d = A2;  // For displaying segment "d"      //    - g -
int e = A1;  // For displaying segment "e"      //    e   c     
int f = A0;  // For displaying segment "f"      //    - d -
int g = 11;  // For displaying segment "g"      //   
 
// Functions' declarations.
void setLed(int ledNum);               // Turns on the LED, ledNum.
void displayClue(int roundNum);        // Displays the current round's sequence.
boolean waitForInput(int buttonNum);   // Checks if the user entered the correct, current input of the current round.
void displayDigit(int digit);          // Displays a signle digit (1 to 9) on the 7-sequence display segment.
void turnOff();                        // Turns off all the segments of the 7-sequence display segment.
 
void setup () 
{
  Serial.begin(9600);
  
  Serial.println("setup");
  
    // Initial pin is zero which corresponds to green, if the pin is less than 4 (pinCount) then add one, which would make the pin number 1 and correspond to red, and so on.
    for(int Pin = 0; Pin < pinCount; Pin++) 
    {
      // Set all LEDs to output.
      pinMode(ledArray[Pin], OUTPUT);
    }
      
    for(int Pin = 0; Pin < pinCount; Pin++)
    {
      // Set all buttons input using pullup resistors, that are built into board. 
      // Additionally, we added 1k-ohm resistors to the buttons.
      pinMode(buttonArray[Pin], INPUT_PULLUP);
    }
   
   // If the analog-input pin is 0, it is unconnected.
   // Random analog noise will cause the call to randomSeed() to generate.
   // Different seed numbers each time the sketch runs.
   // randomSeed() will shuffle the random function that we call during gameplay.
   randomSeed(analogRead(0));  /*** CREDIT TO Katire Kristoff and Monica Houston's on Arduino Project Hub tutorial is due here. ***/
   
   // Set counter pins to OUTPUT
   pinMode(a, OUTPUT);  // a
   pinMode(b, OUTPUT);  // b
   pinMode(c, OUTPUT);  // c
   pinMode(d, OUTPUT);  // d
   pinMode(e, OUTPUT);  // e
   pinMode(f, OUTPUT);  // f
   pinMode(g, OUTPUT);  // g
 }

void loop () 
{
  
    if (gameState == 0)
    {
         int button0 = digitalRead(buttonArray[0]);
         int button1 = digitalRead(buttonArray[1]);  
         int button2 = digitalRead(buttonArray[2]); 
         int button3 = digitalRead(buttonArray[3]); 
         
        // If no buttons are pressed (since button input is pullup: i.e will read LOW when pressed and HIGH when not pressed) we show all buttons pressed, then play pre_game.
        if (button0 && button1 && button2 && button3)
        {
            pre_game();
        }
        // If a button is pressed set up for the game.
        else
        {
            Serial.println("button Pressed"); 
            // Turn leds off before starting game --> function setLed() states that if ledNum is <0 led is LOW.
            setLed(-1);
            // Set the round number to zero so you start on the first round.
            roundNum = 0;
            delay (1000);
            // Go to playing state 
            gameState = 1;
            turnOff();
            // Indicate that first round begins
            // Leave a delay for player to get ready
            displayDigit(1);
            delay(1500);
        }
    }
    
    // Playing game state
    if (gameState == 1)
    {
        gamePlay();
    }
    
    // Winning state
    if (gameState == 2)
    {
        // You win!! - play winning sound and scroll through leds (winDisplay)3 times followed by lose display once for good transition.
        // Delay to give player time to release button press before winning sound plays.
        delay(500);
        winning_sound();
        winDisplay();
        winDisplay();
        winDisplay();
        loseDisplay();
        Serial.println("winDisplay");
        // Delay briefly before running pre_game
        delay (1000);
        turnOff();
        // Reset gameState to zero to call pre_game
        gameState = 0;
    }
    
    // Losing state
    if (gameState == 3)
    {
      // You lose :( - play losing sound and flash leds (loseDisplay)3 times for good transition.
      // Delay to give player time to release button press before losing sound plays.
      delay(500);
      losing_sound();
      loseDisplay();
      loseDisplay();
      loseDisplay();
      Serial.println("loseDisplay");
      // Delay briefly before running pre_game.
      delay (1000);
      turnOff();
      // Go back to the initial state
      gameState = 0;
    } 
}

// Before game is started
// Flick between lights before a button is pressed
void pre_game()
{
  // Check if enough time has elapsed between leds lighting up.
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval1)
  {
    // If enough time has elapsed update lights.
    if (ledState == 0)
    {
      Serial.println("pre green");
      setLed(0);
      ledState = 1;
      turnOff();
      digitalWrite(f, HIGH);
      
    }
    else if (ledState == 1)
    {
      Serial.println("pre red");
      setLed(1);
      ledState = 2;
      turnOff();
      digitalWrite(b, HIGH);
      
    }
    else if (ledState == 2)
    {
      Serial.println("pre yellow");
      setLed(2);
      ledState = 3;
      turnOff();
      digitalWrite(c, HIGH);
      
    }
    else if (ledState == 3)
    {
      Serial.println("pre blue");
      setLed(3);
      ledState = 0;
      turnOff();
      digitalWrite(e, HIGH);
      
    }
    // reset time 
    previousMillis = currentMillis;
  }
}

// Function for while game is playing
void gamePlay()
{
    Serial.println("gamePlay");
    // Pre-load array with random numbers for game
    for ( int i = 0; i < NUMBERTOWIN; i++)
    {
      // Use floor to round number down to nearest integer and random to choose random numbers from 0 to 3 to put in the gameValues array.
      gameValues[i] = floor(random(0,4));
      Serial.println(gameValues[i], DEC);
    }
  
    
    Serial.print("Starting Round ");
    Serial.println(roundNum, DEC);
    for (int r = 0; r < NUMBERTOWIN; r++)
    {

      // Update screen unless it's the first round (where screen updated on start of game)
      if (r != 0) {
        turnOff();
        displayDigit(roundNum + 1);
      }
      
      // Display game sequence for this round
      displayClue(roundNum);
    
      for (int i = 0; i <= roundNum; i++)
      {      
        Serial.print("Waiting for input ");
        Serial.print(i + 1, DEC);
        Serial.print(" of ");
        Serial.print(roundNum + 1, DEC);
        Serial.println("");
    
        // Wait for user input and see if they're correct. If correct, wait for the next input and so on. If one isn't correct, the user fails.
        if (waitForInput(gameValues[i]))
        {
          // Correct input
          if (i == roundNum)
          {
              Serial.println("Correct");
              // check if final round 
              if (roundNum == NUMBERTOWIN - 1)
              {
                Serial.println("You Win!");
               // you won! 
               // set gameState to 2 to run winning fuction
               gameState = 2;
               return;
              }
              else 
              {
                Serial.println("Continue");
              }
          }
        }
        else 
        {
          // Incorrect input
          Serial.println("You Lose!");
  
          // Enter losing state
          gameState = 3;
          return;
        }
      }
      // User made it through the round, increment round number to continue
      roundNum++;
      // Delay briefly so user has time to see start of next clue
      delay(1000);
    }
}

void setLed(int ledNum)
{
  // If the led number is less than zero turn all the leds off
  if (ledNum < 0)
  {
     for (int i = 0; i < pinCount; i++)
     {
        digitalWrite(ledArray[i], LOW);
     }
  }
  else
  {
      // Turn on the specified led, turn off the other leds
      // Turn one and only one led on - if i is the same as the number passed in from pre-game then turn on that light, if it is not the same turn off that light 
      for (int i = 0; i < pinCount; i++)
      {
          if (i == ledNum)
          {
            digitalWrite(ledArray[i], HIGH);
          }
          else 
          {
            digitalWrite(ledArray[i], LOW);
          }
      }
  }
 }

 // Displays the current game sequence
 void displayClue(int roundNum)
 {
    // Turn all lights off.
    setLed(-1);
    for (int i = 0; i <= roundNum; i++)
    {
        // Turn on LEDs that match current round.
        setLed(gameValues[i]);
        delay(750);
        setLed(-1);
        delay(250);
    }
 }

boolean waitForInput(int buttonNum)
{
  // Read all the buttons continuously until a button is pressed. If a button is pressed check if it's correct and if so return true. If not, return false. 
  while(true) 
  {
   int button0 = digitalRead(buttonArray[0]);
   int button1 = digitalRead(buttonArray[1]);  
   int button2 = digitalRead(buttonArray[2]); 
   int button3 = digitalRead(buttonArray[3]); 
   
   // Because we are using INPUT_PULLUP; indicted a button is pressed --> if any button is pressed go to the rest of the code
   if (!button0 || !button1 || !button2 || !button3)
   {
      // Delay briefly to avoid double counting button press
      delay(250);

      // Light up the corresponding led when a button is pressed
      // And play associated music with the button
      if (buttonNum == 0)
      {
        digitalWrite(ledArray[0], HIGH);
        tone(buzzer, 261.63, 250);
        delay(250);
        digitalWrite(ledArray[0], LOW);
      }
      else if (buttonNum == 1)
      {
        digitalWrite(ledArray[1], HIGH);
        tone(buzzer,  329.63, 250);
        delay(250);
        digitalWrite(ledArray[1], LOW);
      }
      else if (buttonNum == 2)
      {
        digitalWrite(ledArray[2], HIGH);
        tone(buzzer, 392, 250);
        delay(250);
        digitalWrite(ledArray[2], LOW);
      }
      else if (buttonNum == 3)
      {
        digitalWrite(ledArray[3], HIGH);
        tone(buzzer, 523, 250);
        delay(250);
        digitalWrite(ledArray[3], LOW);
      }
      
      // Check if correct button was pressed
      if (buttonNum == 0 && button0 == 0)
      {
        Serial.println("0 Pressed");
        return true;
      }
      else if (buttonNum == 1 && button1 == 0)
      {
        Serial.println("1 Pressed");
        return true;
      }
      else if (buttonNum == 2 && button2 == 0)
      {
        Serial.println("2 Pressed");
        return true;
      }
      else if (buttonNum == 3 && button3 == 0)
      {
        Serial.println("3 Pressed");
        return true;
      }
      else 
      {
        return false;
      }
    }
  }
}


void displayDigit(int digit)
{
 //Conditions for displaying segment a
 if(digit!=1 && digit != 4)
 digitalWrite(a,HIGH);
 
 //Conditions for displaying segment b
 if(digit != 5 && digit != 6)
 digitalWrite(b,HIGH);
 
 //Conditions for displaying segment c
 if(digit !=2)
 digitalWrite(c,HIGH);
 
 //Conditions for displaying segment d
 if(digit != 1 && digit !=4 && digit !=7)
 digitalWrite(d,HIGH);
 
 //Conditions for displaying segment e 
 if(digit == 2 || digit ==6 || digit == 8 || digit==0)
 digitalWrite(e,HIGH);
 
 //Conditions for displaying segment f
 if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
 digitalWrite(f,HIGH);
 if (digit!=0 && digit!=1 && digit !=7)
 digitalWrite(g,HIGH);
 
}

// Turns off all lights
void turnOff()
{
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
}

// After win - have lights scroll quickly
void winDisplay()
{
  digitalWrite(ledArray[0], HIGH);
  turnOff();
  digitalWrite(a, HIGH);
  delay(75);
  digitalWrite(ledArray[0], LOW);
  delay(75);
  digitalWrite(ledArray[1], HIGH);
  turnOff();
  digitalWrite(b, HIGH);
  delay(75);
  digitalWrite(ledArray[1], LOW);
  delay(75);
  digitalWrite(ledArray[2], HIGH);
  turnOff();
  digitalWrite(c, HIGH);
  delay(75);
  digitalWrite(ledArray[2], LOW);
  delay(75);
  digitalWrite(ledArray[3], HIGH);
  turnOff();
  digitalWrite(c, HIGH);
  delay(75);
  digitalWrite(ledArray[3], LOW);
  delay(75);
  digitalWrite(ledArray[2], HIGH);
  turnOff();
  digitalWrite(d, HIGH);
  delay(75);
  digitalWrite(ledArray[2], LOW);
  delay(75);
  digitalWrite(ledArray[1], HIGH);
  turnOff();
  digitalWrite(e, HIGH);
  delay(75);
  digitalWrite(ledArray[1], LOW);
  delay(75);
  digitalWrite(ledArray[0], HIGH);
  turnOff();
  digitalWrite(f, HIGH);
  delay(75);
  digitalWrite(ledArray[0], LOW);
  delay(75);
  turnOff();
  digitalWrite(g, HIGH);
  delay(75);
  turnOff();
}

void winning_sound(void)
{
  // Play winning celebration
  Serial.println("buzzer1");
  tone(buzzer, 294, 250);
  delay(200);
  tone(buzzer, 294, 250);
  delay(200);
  tone(buzzer, 294, 250);
  delay(200);
  tone(buzzer, 392, 500);
  delay(500);
  Serial.println("second 392");
  tone(buzzer, 392, 250);
  delay(200);
  tone(buzzer, 440, 250);
  delay(200);
  tone(buzzer, 392, 250);
  delay(200);
  tone(buzzer, 440, 250);
  delay(200);
  tone(buzzer, 494, 500);
}

// Quickly turn on and turn off lights to signal loss
void loseDisplay()
{
  digitalWrite(ledArray[0], HIGH);
  digitalWrite(ledArray[1], HIGH);
  digitalWrite(ledArray[2], HIGH);
  digitalWrite(ledArray[3], HIGH);
  delay(200);
  digitalWrite(ledArray[0], LOW);
  digitalWrite(ledArray[1], LOW);
  digitalWrite(ledArray[2], LOW);
  digitalWrite(ledArray[3], LOW);
  delay(200);
}
// Make a losing sound
void losing_sound(void)
{
  Serial.println("losing_sound");
  tone(buzzer, 98, 250);
  delay(250);
   tone(buzzer, 93, 250);
  delay(250);
   tone(buzzer, 87, 250);
  delay(250);
}
