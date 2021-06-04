#include <SPI.h>
#include "RF24.h" // the library associated with nrf24l01 wireless module (nordic)

const int n = 2; // number of channels
int analogPin[n] = {A0, A1};
byte channel[n], send_byte; // kanal sinyalleri ve robota gönderilen komut: robotu ileri-geri ve kendi etrafında saat yönü ve tersi hareket ettirmek
RF24 radio(7, 8); // digital pins that CE and CSN are connected, respectively.
const uint64_t pipe = 0xE8E8F0F0E1LL; // the address of the modem, that will receive data from Arduino

void setup() {
  radio.begin(); // nrf24l01 kablosuz haberleşme başlatılıyor
  radio.openWritingPipe(pipe); // sets the address of the receiver to which the program will send data
}

void loop() {
  for (int i=0; i<n; i++)
    channel[i] = map(analogRead(analogPin[i]), 0, 1023, 0, 255);
  send_byte = B00000000;
  if(channel[0] < 80)send_byte |= B00000001;                  //If the variable received_data[0] is smaller then 80 set bit 0 of the send byte variable
  if(channel[0] > 170)send_byte |= B00000010;                 //If the variable received_data[0] is larger then 170 set bit 1 of the send byte variable
  if(channel[1] < 80)send_byte |= B00001000;                  //If the variable received_data[1] is smaller then 80 set bit 3 of the send byte variable
  if(channel[1] > 170)send_byte |= B00000100;
  if(send_byte)radio.write(&send_byte, 1);
  delay(40);
}
