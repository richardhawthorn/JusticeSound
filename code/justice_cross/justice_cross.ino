/*
 * Justice Cross
 * Richard Hawthorn
 * richardhawthorn.com
 * 2016-11-09
 */

/*
 * Pin setup
 */
int led_pins[] = {0,1,2,3,10,9};
int btn = 8;

/*
 * Globals
 */
int leds[48];
int menu = 0;
long loopPos = 0;
int led_loop = 0;
int on = 1;
int counts[] = {1, 50, 100};

/*
 * Setup the board
 */
void setup() {

  //delay for 2 seconds before getting started  
  delay(2000);

  //setup the button pin
  pinMode(btn, INPUT_PULLUP);

}


/*
 * Main Loop
 */
void loop() {

  determineLedStatus();
  displayLeds();
  checkButton();

}

/*
 * Check the button
 */
void checkButton(){

  if (!digitalRead(btn)){
    menu++;
    delay(500);
  }
  
}

/*
 * Loop through the menu and determine what our leds should be doing
 */
void determineLedStatus(){

  loopPos++;
   
  if (menu > 3){
    
    menu = 0;
  
  } else if (menu == 0){
    
    on = true;
    
  } else if (menu == 3){

    if (loopPos > 10){
       loopPos = 0;

       for(int p = 0; p <= 47; p++){
          leds[p] = random(0,2);
       }
  
    } 

  } else {

    if (loopPos < (counts[menu] / 2)){
       on = true;
    } else {
       on = false;
    }

    if (loopPos > counts[menu]){
      loopPos = 0;
    }

  }

}

/*
 * Display our pattern on the leds
 */
void displayLeds(){

  led_loop = 0;

  for (int i = 0; i <= 5; i++){
    pinMode(led_pins[i], OUTPUT); 
    digitalWrite(led_pins[i], LOW); 

    for (int j = 0; j <= 5; j++){
      if (i != j){

        if (menu == 3){
          on = leds[led_loop];
        }

        led_loop++;
        
        if (on){
          pinMode(led_pins[j], OUTPUT);
          digitalWrite(led_pins[j], HIGH); 
        }
      }
    }

    delayMicroseconds(600);

    for (int k = 0; k <= 5; k++){
      if (i != k){
          digitalWrite(led_pins[k], LOW); 
          pinMode(led_pins[k], INPUT);
      }
    }
    
    digitalWrite(led_pins[i], HIGH); 
    pinMode(led_pins[i], INPUT); 
    
  }

}

