const int res = 13;		// pin de la LED simulant une résistance chauffante
const int valid = 12;	// pin de la LED confirmant la validité des calculs
const int invalid = 11;	// pin de la LED invalidant les calculs
// liste des ln de 0.01 à 0.59 (pour calculer la rosée)
float ln[60] = {-4.61, -3.91, -3.51, -3.22, -3.0, -2.81, -2.66, -2.53, -2.41, -2.3, -2.21, -2.12, -2.04, -1.97, -1.9, -1.83, -1.77, -1.71, -1.66, -1.61, -1.56, -1.51, -1.47, -1.43, -1.39, -1.35, -1.31, -1.27, -1.24, -1.2, -1.17, -1.14, -1.11, -1.08, -1.05, -1.02, -0.99, -0.97, -0.94, -0.92, -0.89, -0.87, -0.84, -0.82, -0.8, -0.78, -0.76, -0.73, -0.71, -0.69, -0.67, -0.65, -0.63, -0.62, -0.6, -0.58, -0.56, -0.54, -0.53};
const float a = 17.27;	// constate nécessaire pour calculer la rosée
const float b = 237.7;	// constate nécessaire pour calculer la rosée

void setup() {
  pinMode(13, OUTPUT);	// Initialisation du pin de la LED "res"
  pinMode(12, OUTPUT);	// Initialisation du pin de la LED "valid"
  pinMode(11, OUTPUT);	// Initialisation du pin de la LED "invalid"
  Serial.begin(9600);	// Initialisation du moniteur série
}

void loop() {
  
  int temperature = analogRead(A0);		// Lecture de la valeur brute correspondant à la température
  temperature = map(temperature, 20, 358, -40, 125);	// Réglage pour faire correspondre les valeurs bruts de la température récupérées en analogique aux valeurs correspondant à la température en °C
  
  int humidity = analogRead(A1);		// Lecture de la valeur brute correspondant à l'humidité relative
  humidity = map(humidity, 0, 1023, 0, 100);			// Réglage pour faire correspondre les valeurs bruts de l'humidité relative récupérées en analogique aux valeurs correspondant à l'humidité en %
  
  // Conditions du domaine de validité (0 < temperature <60°C ; 1% < humidity < 100%)
  if (temperature > 0 and temperature < 60 and humidity > 1 and humidity < 100){
  	float rosee = (b*((a*temperature)/(b+temperature)+ln[humidity]))/(a-((a*temperature)/(b+temperature)+ln[humidity]));
    
    // Conditions du domaine de validité (0 < rosee < 50°C)
    if (rosee > 0 and rosee < 50){
      Serial.println(rosee);		// Affiche la valeur de la rosée dans la console
      
      // Détecter présence de buée
      if (rosee > temperature or rosee == temperature){
        // Mesure valide
      	digitalWrite(invalid, LOW);
        analogWrite(res, 255);
        analogWrite(valid, 255);	// Allumer la résistance chauffante
      }
      else{
        // Mesure valide
      	digitalWrite(res, LOW);
        digitalWrite(invalid, LOW);
        analogWrite(valid, 255);
      }
    
    }
    else{
      // Mesure invalide
      digitalWrite(res, LOW);
      digitalWrite(valid, LOW);
      analogWrite(invalid, 255);
    }
  }
  else{
  	// Mesure invalide
  	digitalWrite(res, LOW);
    digitalWrite(valid, LOW);
    analogWrite(invalid, 255);
  }
  
  // Afficher la température et l'humidité relative dans la console
  Serial.println(temperature);
  Serial.println(humidity);
  
  // Delai de 0.25 seconde entre les mesures
  delay(250);

}