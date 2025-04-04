// Duas formas de definir os pinos:
// Pela numeração do NodeMCU:



// Pela numeração do GPIO:
#define LED_FRONT   D8
#define LED_BACK   1

void setup()
{
  // Configura pinos como saída
  pinMode(LED_FRONT, OUTPUT);
  digitalWrite(LED_FRONT, HIGH);  // Configura pinos como saída
  pinMode(LED_BACK, OUTPUT);
  digitalWrite(LED_BACK, HIGH);
}

void loop()
{

}