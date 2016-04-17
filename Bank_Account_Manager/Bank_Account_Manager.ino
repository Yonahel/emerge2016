#include <Keypad.h>
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte ROWS = 4;
const byte COLS = 4;
char keyboard[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {53, 51, 49, 47}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {45, 43, 41, 39}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(keyboard), rowPins, colPins, ROWS, COLS);


String snumber = "";
float number = 0.0;
char temp;
char temp1;
int a = 0;


void setup()
{
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.noAutoscroll();
}

void loop()
{
  if(Serial.available())
  {
    snumber = Serial.readString();
    a = 1;
  } 
  if(a==1){  
    number = atof(snumber.c_str());
    Serial.println(number);
    snumber = "";
    a=0;
  }  
  temp = customKeypad.getKey();
  if(temp == 'A')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Input Balance: ");
    while(1){
      temp1 = customKeypad.getKey();
      if(temp1 == '*'){
        snumber+=".";
      }
      else if (temp1 == '#'){
        number = atof(snumber.c_str());
        snumber = "";
        break;
      }
      else if(temp1 =='A' || temp1 == 'B' || temp1 == 'C' || temp1 == 'D'){
        int temp2 = 1;
      }
      else if(temp1 != 0){
        snumber+=temp1; 
        lcd.setCursor(0, 1);
        lcd.print(snumber); 
      }
    }
  }
  else if(temp == 'B')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Input Deposit: ");
    while(1){
      temp1 = customKeypad.getKey();
      if(temp1 == '*'){
        snumber+='.';
      }
      else if (temp1 == '#'){
        number += atof(snumber.c_str());
        snumber = "";
        break;
      }
      else if(temp1 != 0){
        snumber+=temp1; 
        lcd.setCursor(0, 1);
        lcd.print(snumber); 
      }
    }
  }
  else if(temp == 'C')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Input Withdrawal Amount: ");
    while(1){
      temp1 = customKeypad.getKey();
      if(temp1 == '*'){
        snumber+='.';
      }
      else if (temp1 == '#'){
        number -= atof(snumber.c_str());
        snumber = "";
        break;
      }
      else if(temp1 != 0){
        snumber+=temp1;
        lcd.setCursor(0, 1);
        lcd.print(snumber);  
      }
    }
  }
  else if(temp == 'D')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Current Balance: ");
    // Print the current balance to the LCD.:
    lcd.setCursor(0, 1);
    lcd.write("$");
    // Print the balance
    lcd.print(number);
    Serial.println("Yo");
  }
}
