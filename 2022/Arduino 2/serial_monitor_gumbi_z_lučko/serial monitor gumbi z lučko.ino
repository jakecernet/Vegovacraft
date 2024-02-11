int leviGumb = 0;
int desniGumb = 0;

int levoStikalo = 0;
int leviGumbStaroStanje = 0;

int stanjeLED = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(3, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT); // 13

  Serial.begin(9600);  // Začnemo serijski vmesnik
}

void loop() {
  // put your main code here, to run repeatedly:

  // ORIGINAL

  // leviGumb = digitalRead(8) + 2;
  // desniGumb = digitalRead(9);

  //NEGACIJA
  leviGumb = !digitalRead(3);
  if(leviGumb != leviGumbStaroStanje){
    if(leviGumbStaroStanje == 0){
      digitalWrite(LED_BUILTIN, stanjeLED);
      stanjeLED = !stanjeLED;
    }
  }

  leviGumbStaroStanje = leviGumb;
  desniGumb = 1 - digitalRead(5);

  int in = leviGumb && desniGumb;
  int ali = leviGumb || desniGumb; // || - ALTGR + W
  int xali = leviGumb ^ desniGumb; // ^ - ALTGR + 3 (2x) ali ALTGR + 3 nato PRESLEDEK

  Serial.print("Min:-0.5, Max:12, ");
  Serial.print("Levi:");
  Serial.print(leviGumb + 2);
  Serial.print(", Desni:");
  // Serial.println(primer);
  Serial.print(desniGumb);
  Serial.print(", IN:");
  Serial.print(in + 4);
  Serial.print(", ALI:");
  Serial.print(ali + 6);
  Serial.print(", XOR:");
  Serial.print(xali + 8);
  Serial.print(", LEVI2:");
  Serial.println(levoStikalo); // 1. pritidnemo lev gumb je 1 in ostane dokler 2. ne pritisnemo gumba nato postane 0;

  delay(200);
  }