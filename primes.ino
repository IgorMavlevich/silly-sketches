//Primes sketch by Gear206
// ###POINTERS!!!###
//done in 1 day
//TODO: proper string -> number conversion
//also: make use of the memo array
//copyright 22.11.2016

#define BAUDRATE 9600    //It's handy to have it like this, no need
//for searching it in the code
#define uint unsigned int //"unsigned int" is kind of long
#define LED 13 //variables are using space, while #define is
//is a command for the the compiler to replace one thing using 
//another

uint index = 0; //We don't need negative values, but we may need to
//store somewhat large numbers
uint prime = 2;
char inputStr[3];
uint memo[100];


void setup(){
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  
  for (byte i; i < 100; i++){//Let's initialise the array
    memo[i] = 0;
  }
  memo[0] = 2;//And put the first elements in it
  memo[1] = 3;
  
  Serial.begin(BAUDRATE);
  Serial.println( //This string came out really long
    "Please enter index of your prime number (up to 3 digits):"
  );
}

void loop(){
  //Reinitialise everything every time the loop closes:
  index = 0;
  prime = 2;
  
  for (byte i; i < 3; i++){
    inputStr[i] = 48;//48 means '0' in ASCII
  }
  //Huge mess incoming. Doesn't work
  if (Serial.available()){
    byte i = 0;
    while ( i < 3){
      inputStr[i]= (char)Serial.read();
      i++;
    }
    index = string2byte(inputStr);
  }
  
  if (index > 0){
    //Isn't in nice to tell the user when the chip is buisy
    digitalWrite(LED, HIGH);//using the embedded LED
    searchPrime(&index);// POINTER!
    digitalWrite(LED, LOW);
    Serial.print("Prime(");//On a computer it would be much
    Serial.print(index+1);//simplier, than this thing
    Serial.print(") = ");
    Serial.println(prime);
  }
}

byte string2byte(char input[3]){//Terrible ahead
  byte out = 0;
  for (byte i = 0; i < 3; i++){//This thing is insane
    input[i] -= 48;//And it doesn't even work
  }
  out = input[0];
  Serial.println(out);
  out += input[1]*10;
  Serial.println(out);
  out += input[2]*100;
  Serial.println(out);
  return out;
}

uint searchPrime(uint *index){//Yess, pointers!
  *index -= 1;//Using pointer, we don't make copy of the original
  if (*index == 0){//variable - we manipulate the original one
    return 0;//Why do I need it here?
  }
  prime = 3;
  if (*index == 1){
    return 0;
  }
  for (byte i = 2; i <= *index; i++){
    prime += 2;
     while ( !(checkPrime(prime)) ){
       prime += 2;
     }
     memo[i] = prime;
  }
}

boolean checkPrime(uint input){
  uint border = input/2;
  uint i = 0;
  while (memo[i] < border){
    if (input%memo[i] == 0){
      return false;
    }
    i++;
  }
  return true;
}
