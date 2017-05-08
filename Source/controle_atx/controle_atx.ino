// Ce programme pour Arduino Uno sert à controler une alimentation ATX
// pour l'allumer et l'éteindre quand on presse un bouton poussoir

// Connection :
// L'arduino est alimenté par le 5VSB de l'alim ATX (Pin 9 (Violette) du connecteur ATX), la GND au GND de l'ATX :-)
// La pin 13 de l'arduino est connectée à la PS_ON de l'ATX (Pin 16 (Verte))
//      Celle-ci est active à niveau bas et sert à envoyer le signal d'allumage à l'alim ATX
//      Si elle est maintenue à état haut, elle sert à l'éteindre
// La Pin 12 de l'arduino est connectée à une des pins du bouton poussoir, avec une résistance de rappel à la masse en //
// La deuxième Pin du bouton est reliée au 5V

int PS_ON = 13;         // Numéro de la pin qui sert à connecter le PS_ON
int Bouton = 12;        // Numéro de la pin qui sert à connecter le bouton
int Cpt;                // Compteur qui gère le temps qu'il faut attendre avant de prendre en compte l'appui
int EtatSortie = 1;     // Sert à controler l'état de sortie, qui va basculer entre éteint et allumé
int AntiRebond = 0;     // Sert à gérer le fait qu'il faille relacher le bouton avant de pouvoir prendre un nouvel ordre

void setup()
{
  // put your setup code here, to run once:
  pinMode(PS_ON, OUTPUT);      // sets the digital pin as output
  digitalWrite(PS_ON, LOW);    // sets the LED off
  pinMode(Bouton, INPUT);      // sets the digital pin as output
  EtatSortie = 1;
  Cpt = 0;
}

void loop()
{
  // Boucle principale

  // Lecture du bouton poussoir
  if (digitalRead(Bouton) == HIGH)
  {

    // Il faut relacher le bouton, sinon, on n'incrémente pas !
    if (AntiRebond == 0)
      Cpt++;
  }
  else
  {

    // On a relaché le bouton trop tot !
    Cpt        = 0;

    // Mais on l'a relaché, donc on pourra ré-appuyer dessus
    AntiRebond = 0;
  }

  // Si on a appuyé suffisement longtemps
  if (Cpt > 10)
  {

    // On fait l'extinction ou l'allumage
    if (EtatSortie == 1)
    {
      poweron();
    }
    else
    {
      poweroff();
    }

    // Remise du compteur à zéro (pas nécessaire ?)
    Cpt = 0;

    // Par contre, il va falloir le relacher ce bouton !
    AntiRebond = 1;
  }
  delay(100);
}

void poweron()
{
    digitalWrite(PS_ON, LOW);     // Allumer la LED et éteindre l'alim
    EtatSortie = 0;
}

void poweroff()
{
    digitalWrite(PS_ON, HIGH);   // éteindre la LED et allumer l'alim
    EtatSortie = 1;
}

