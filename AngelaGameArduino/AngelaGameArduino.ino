int initialNumber = 0;
int turn = 0;
int numberTurn[100];
int reachNumber = 0;


void setup()
{  
  Serial.begin(9600);
  Serial.println("***benvenuto in Angela Game***");
  partenza();
}

void loop() 
{
  int controlWL = winOrLoseControl(initialNumber);
  switch(controlWL)
  {
    case 1:    
            turnoDiChi();
            addNumberSerial();
            turn++;break;
    case 0:
            turn--;turnoDiChi();    
            Serial.println(" ha vinto");
            attendiInput();
            partenza();break;
    case 2:
            turn--;turnoDiChi();
            Serial.println("ha perso");
            attendiInput();
            partenza();break;
            
    default:break;           
  }
}

void addNumberSerial()
{
  bool finish = false;
  while(!finish)
  {
    attendiInput();
    int numero = Serial.parseInt();
    Serial.read();
    if(numberControl(numero))
    {
      finish = true;
      initialNumber += numero;
      numberTurn[turn] = numero;
      Serial.println((String)numero + " | " + (String)initialNumber);
    }
    else
    {
      Serial.print("numero non accettato ->");
    }
  }
}

bool numberControl(int number)
{
  if((numberTurn[turn-1] + number) != 7 && number < 7 && number > 0 || turn == 0 && number == 0){return true;}  
  return false;
}

int winOrLoseControl(int number)
{
  if(number == reachNumber){return 0;}
  if(number < reachNumber){return 1;}
  if(number > reachNumber){return 2;}
}

void turnoDiChi()
{
  if(turn%2){Serial.print("Giocatore2 -> ");}
  else{Serial.print("Giocatore1 -> ");}
}

void attendiInput()
{
  Serial.read();
  while(!Serial.available()){}
}

void partenza()
{
  Serial.println("inserisci numero da raggiungere : ");
  reachNumber = 0;
  while(reachNumber > 100 || reachNumber < 29)
  {
      attendiInput();
      reachNumber = Serial.parseInt();
      Serial.read();
      if(reachNumber > 100 ||  reachNumber < 29){ Serial.println(" il numero deve essere compreso tra 30 e 99"); }
  }
  Serial.println("numero da raggiungere -> " + (String)reachNumber);
  initialNumber = 0;
  turn = 0;
}
