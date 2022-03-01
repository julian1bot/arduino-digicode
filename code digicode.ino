
 //Libraries
#include <Keypad.h> //https://github.com/Chris--A/Keypad
#include <Wire.h>  // inclure la bibliothèque permettant la communication par le protocole I2C
#include "rgb_lcd.h" // inclure la bibliothèque pour l'écran LCD
#include <Servo.h>
 

//Constants
#define ROWS 4 // 4lignes
#define COLS 4 // 4 colonnes
#define DLENGTH 4 // nombre de valeur que contien le code (donc code a {DLENGTH} chiffre)
 
Servo myservo;
rgb_lcd lcd; 
int servomoteur = 3;
// Led
int ledv = 3; 
int ledr = 4;
int led_pave = 5;

// capteur
int capt_move = 2;


//Parametre 
const char kp4x4Keys[ROWS][COLS]  = {
{'1','2','3','A'}, 
{'4','5','6','B'}, 
{'7','8','9','C'}, 
{'*','0','#','D'}
}; // faire les lignes et colonnes et assigner une valeurs pour chaque bouton 
int pos_init = 0;
int pos = 180;

byte rowKp4x4Pin [4] = {13, 12, 11, 10}; // pin des 4 lignes
byte colKp4x4Pin [4] = {9, 8, 7, 6}; // pin des 4 colonnes
char digits[DLENGTH]; // dit que digits doit avoir {DLENGTH} valeur
char code[]= "0000"; // 1309
int index=0; 

//Variables
Keypad kp4x4  = Keypad(makeKeymap(kp4x4Keys), rowKp4x4Pin, colKp4x4Pin, ROWS, COLS); // kp4x4 correponds a tout les parametres dit precedament 
void setup() {
 myservo.attach(servomoteur);
 //Init Serial USB
 Serial.begin(9600); // setup du moniteur serie sur 9600
 Serial.println(F("Initialize System")); // envoyer un message dans le moniteur pour signalé l'initialisation du systeme 
  pinMode(ledv, OUTPUT); // appeler la led sur le pin {ledv} en sortie
    pinMode(ledr, OUTPUT); // appeler la led sur le pin {ledr} en sortie
    pinMode(led_pave, OUTPUT); // appeler la led sur le pin {led_pave} en sortie
    lcd.begin(16, 2);
    lcd.clear();   // effacer l'écran

}
void loop() {
 readKp4x4(); // appeler la fonction readKp4x4() qui permet de lire ce qui est écrit dans le pavé numerique 
 capteur();
}
void readKp4x4() { /* fonction readKp4x4 */
 // lire les boutons avec keypad
 char customKey = kp4x4.getKey(); // customKey est la valeurs du bouton qui VIENT d'etre cliqué
 if (customKey) {
   // Serial.println(customKey);
   digits[index]=customKey; // index est le numero de la valeur donc dans 2954 ==>     2 => valeur 1,    9 => valeur 2,    5 => valeur 3,     4 => valeur 4
   index=index+1; // a chaque clique on change la valeur a changer donc index +1 pour que ca change pas que UNE valeur
   if(index==DLENGTH){ // si la valeur de {index} et egale a celle de {DLENGTH}
     Serial.println(digits); // envoyer dans le moniteur le code mis
     index=0; // reset l'index a ca valeur initialle 
     if(strcmp(digits,code)==0){ // si le code est bon alors..
       Serial.println(F("Code bon !")); // envoyer dans le moniteur "code bon !0"
         digitalWrite(ledv, HIGH); // allumer la led vert 
              lcd.setCursor(6, 0);
              myservo.write(pos); 
              lcd.print("CODE");    
              lcd.setCursor(5, 1);   
              lcd.print("VALIDE");
              delay(1000);
              lcd.clear();
          delay(1000); // laissé allumé pendant 2sec pour dire que le mdp est bon 
          digitalWrite(ledv, LOW); // arreter la led vert
          myservo.write(pos_init); 
       }     
     if(strcmp(digits,code)!=0){ // si le code est faux alors...
       Serial.println(F("code faux !")); // envoyer dans le moniteur 'code faux !'
         digitalWrite(ledr, HIGH); // allumer la led rouge
              lcd.setCursor(6, 0);  
              lcd.print("CODE");    
              lcd.setCursor(4, 1);   
              lcd.print("INVALIDE");
              delay(1000);
              lcd.clear();
         delay(1000); // laissé allumé pendant 2sec pour dire que le mdp est faux
         digitalWrite(ledr, LOW); // arreter la led rouge 
     }
   }
 }
}
void capteur(){
  
  if(analogRead(A1)< 600){
      //Serial.println(analogRead(A1));
       if(digitalRead(capt_move)==HIGH){
            // Serial.println("MOUVEMENT CAPTERRRRRRRRRRR");
        Serial.print("\t");
         digitalWrite(led_pave, HIGH); // allumer la led blanche
          lcd.clear();   // effacer l'écran
              lcd.setCursor(6, 0);  
              lcd.print("LAMPE");    
              lcd.setCursor(6, 1);   
              lcd.print("lancer");
              delay(500);
              lcd.clear();
         delay(1500); // laissé allumé pendant 2sec pour dire que le mdp est faux
         digitalWrite(led_pave, LOW); // arreter la led blasf    
           
       }
  }
}

/*
void capteur(){
  if(analogRead(A0)< 600){
      Serial.print(analogRead(A0))
       if(digitalRead(capt_move)==HIGH){
         digitalWrite(led_pave, HIGH); // allumer la led blanche
         delay(2000); // laissé allumé pendant 2sec pour dire que le mdp est faux
         digitalWrite(led_pave, LOW); // arreter la led blasf      
       }
  }
}
*/

  
/*
les variables :
 -strcmp: elle compare deux chaînes de caractères donc le code et Ce qu'on a mis en code 


*/
