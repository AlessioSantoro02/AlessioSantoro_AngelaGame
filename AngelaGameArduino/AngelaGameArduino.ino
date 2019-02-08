#define Button1 8
#define Button2 9
#define Button3 10

int initialNumber = 40;
int numberTurn[100];
int reachNumber = 0;
int turn = 0;

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  
pinMode(Button1, INPUT_PULLUP);
pinMode(Button2, INPUT_PULLUP);
pinMode(Button3, INPUT_PULLUP);

lcd.clear();
lcd.begin(16, 2);
lcd.println("***benvenuto in Angela Game***");
//scorriScrittaLcd(true,3000);
lcd.clear();
partenza();

}

void loop() 
{
  int controlWL = winOrLoseControl(initialNumber);
  lcd.clear();
  switch(controlWL)
  {
    case 1:    
            turnoDiChi();
            addNumberlcd();
            turn++;break;
    case 0:
            turn--;turnoDiChi();    
            lcd.println(" ha vinto");
            attendiInput();
            partenza();break;
    case 2:
            turn--;turnoDiChi();
            lcd.println("ha perso");
            attendiInput();
            partenza();break;
            
    default:break;           
  }
}

void addNumberlcd()
{
  bool finish = false;
  while(!finish)
  {
    int numero = attendiInput();
    lcd.clear();
    if(numberControl(numero))
    {
      finish = true;
      initialNumber += numero;
      numberTurn[turn] = numero;
      lcd.println((String)numero + " | " + (String)initialNumber);
    }
    else
    {
      lcd.print("numero non accettato ->");
    }
  }
}

bool numberControl(int number)
{
  if((numberTurn[turn - 1] + number) != 7 && number < 7 && number > 0 || turn == 0 && number == 0){return true;}  
  return false;
}

int winOrLoseControl(int number)
{
  if(number == reachNumber){return 0;}
  if(number < reachNumber){return 1;}
  if(number > reachNumber){return 2;}
  return 0;
}

void turnoDiChi()
{
  if(turn%2){lcd.print("Giocatore2 -> ");}
  else{lcd.print("Giocatore1 -> ");}
}

int attendiInput()
{
  int numero = 0;
  while(digitalRead(Button3) == HIGH)
  {
    lcd.clear();
    lcd.print(numero);
    if(digitalRead(Button1) == LOW){numero++;delay(300);}
    if(digitalRead(Button2) == LOW){numero--;delay(300);}
  }
  while(digitalRead(Button3) == LOW){}
  return numero;
}

void partenza()
{
  lcd.println("inserisci numero da raggiungere : ");
  reachNumber = 0;
  while(reachNumber > 100 || reachNumber < 29)
  {
      reachNumber = attendiInput();
      if(reachNumber > 100 ||  reachNumber < 29){ lcd.println(" il numero deve essere compreso tra 30 e 99"); }
  }
  lcd.println("numero da raggiungere -> " + (String)reachNumber);
  initialNumber = 0;
  turn = 0;
}


void scorriScrittaLcd(bool cheParte , int millisecond , int linea , String cosa)
{
   int millisDaRaggiungere = millis() + millisecond;
   while(millis() < millisDaRaggiungere) 
   {
     if(cheParte){scrollInFromLeft(linea,"ciao");}
     else{scrollInFromRight(linea,"cosa");}
     delay(300);
   }
}
void scrollInFromLeft (int line,String stringa) 
{
  int i = 40 - stringa.length();
  line = line - 1;
  for (int a = i; a <= i + 16; j++) 
  {
    for (int b = 0; b <= 15; b++) 
    {
      lcd.print(" ");
    }
    lcd.setCursor(a, line);
    lcd.print(stringa);
    delay(150);
  }

}
void scrollInFromRight (int line, String stringa)
{
  int i = stringa.length();
  for (int a = 16; a >= 0; a--) 
  {
    lcd.setCursor(0, line);
    for (int b = 0; b <= 15; b++) 
    {
      lcd.print(" ");
    }
    lcd.setCursor(a, line);
    lcd.print(stringa);
    delay(150);
  }
}
