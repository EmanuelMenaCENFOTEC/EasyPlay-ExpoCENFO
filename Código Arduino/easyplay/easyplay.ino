#include <BleMouse.h>
#include <BleKeyboard.h>
#include <EasyMFRC522.h>

char direccionJoystick = 'e';

int modo[4] = {2, 2, 1, 2};

unsigned int boton[4] = {0xD8, 0xD7, 1, 0xB1};

bool toggle[4] = {true, false, false, false};

const int pines[4] = {35, 34, 36, 39};

const int joystickX = 32;
const int joystickY = 33;

int ejeX = 0;
int ejeY = 0;

int sensHorizontal = 15;
int sensVertical = 10;

int sensX = 0;
int sensY = 0;

int multiplicadorEjeX = 1;
int multiplicadorEjeY = 1;

EasyMFRC522 rfidReader(21, 5);

/**
 * Configura el entorno inicial para el funcionamiento del joystick y el lector RFID.
 */
void setup() {
  Serial.begin(115200);

  Keyboard.begin();
  Mouse.begin();

  rfidReader.init();

  pinMode(pines[0], INPUT);
  pinMode(pines[1], INPUT);
  pinMode(pines[2], INPUT);
  pinMode(pines[3], INPUT);

  definirDireccion(direccionJoystick);
}

/**
 * Función principal de bucle que se ejecuta repetidamente. Maneja la interacción con los pines y
 * mueve el mouse basado en la posición del joystick.
 */
void loop() {
  interactuar(pines[0], modo[0], boton[0]);
  interactuar(pines[1], modo[1], boton[1]);
  interactuar(pines[2], modo[2], boton[2]);
  interactuar(pines[3], modo[3], boton[3]);

  ejeX = valorEje(joystickX, sensX) * multiplicadorEjeX;
  ejeY = valorEje(joystickY, sensY) * multiplicadorEjeY;

  if (direccionJoystick == 'N' || direccionJoystick == 'n' || direccionJoystick == 'S' || direccionJoystick == 's') {
    Mouse.move(ejeX, ejeY, 0);
  } else {
    Mouse.move(ejeY, ejeX, 0);
  }

  delay(10);
}

/**
 * Interactúa con un dispositivo basado en el estado del pin y el modo especificado.
 * 
 * @param pin El pin que se está leyendo.
 * @param modo El modo de interacción (1 para mouse, 2 para teclado).
 * @param accion La acción a realizar (presionar/release).
 */
void interactuar(int pin, int modo, unsigned int accion) {
  if (!digitalRead(pin)) {
    if (modo == 1 && !Mouse.isPressed(accion)) {
      Mouse.press(accion);
    } else if (modo == 2) {
      Keyboard.press(accion);
    }
  } else {
    if (modo == 1) {
      Mouse.release(accion);
    } else if (modo == 2) {
      Keyboard.release(accion);
    }
  }
}

/**
 * Calcula el valor del eje del joystick con sensibilidad aplicada.
 * 
 * @param entrada El pin analógico del joystick.
 * @param sensibilidad La sensibilidad aplicada al eje.
 * @return El valor mapeado del eje con sensibilidad aplicada.
 */
int valorEje(int entrada, int sensibilidad) {
  int valor = map(analogRead(entrada), 0, 4095, -sensibilidad, sensibilidad);
  double threshold = sensibilidad - (sensibilidad * 0.7);

  if (valor >= -threshold && valor <= threshold) {
    valor = 0;
  }

  return valor;
}

/**
 * Define la dirección del joystick y ajusta los multiplicadores de los ejes y sensibilidades.
 * 
 * @param dir La dirección del joystick ('N', 'E', 'S', 'W').
 */
void definirDireccion(char dir) {
  if (dir == 'N' || dir == 'n') {
    multiplicadorEjeX = -1;
    multiplicadorEjeY = -1;
    sensX = sensHorizontal;
    sensY = sensVertical;
  } else if (dir == 'E' || dir == 'e') {
    multiplicadorEjeX = 1;
    multiplicadorEjeY = -1;
    sensX = sensVertical;
    sensY = sensHorizontal;
  } else if (dir == 'S' || dir == 's') {
    multiplicadorEjeX = 1;
    multiplicadorEjeY = 1;
    sensX = sensHorizontal;
    sensY = sensVertical;
  } else if (dir == 'W' || dir == 'w') {
    multiplicadorEjeX = -1;
    multiplicadorEjeY = 1;
    sensX = sensVertical;
    sensY = sensHorizontal;
  }
}
