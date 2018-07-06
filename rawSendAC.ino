/* rawSend.ino Example sketch for IRLib2
 *  Illustrates how to send a code Using raw timings which were captured
 *  from the "rawRecv.ino" sample sketch.  Load that sketch and
 *  capture the values. They will print in the serial monitor. Then you
 *  cut and paste that output into the appropriate section below.
 */
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender

IRsendRaw mySender;

void setup() {
  Serial.begin(19200);
  delay(2000); while (!Serial); //delay for Leonardo
  Serial.println(F("Every time you press a key is a serial monitor we will send."));
}
/* Cut and paste the output from "rawRecv.ino" below here. It will 
 * consist of a #define RAW_DATA_LEN statement and an array definition
 * beginning with "uint16_t rawData[RAW_DATA_LEN]= {…" and concludes
 * with "…,1000};"
 */

#define RAW_DATA_LEN_1 200



uint16_t rawData_1[RAW_DATA_LEN_1]={4550, 4210, 550, 1586, 550, 546, 702, 1438, 546, 1618, 570, 498, 570, 526, 546, 1590, 574, 522, 570, 498, 574, 1590, 546, 522, 678, 418, 574, 1562, 574, 1590, 574, 494, 574, 1590, 574, 494, 574, 522, 574, 494, 574, 1590, 574, 1562, 578, 1586, 574, 1590, 574, 1566, 574, 1590, 574, 1562, 574, 1590, 574, 494, 574, 522, 574, 494, 574, 522, 574, 494, 574, 522, 574, 1562, 574, 1590, 574, 1562, 578, 1586, 578, 494, 574, 518, 574, 498, 574, 1586, 578, 494, 574, 518, 578, 494, 574, 518, 578, 1562, 574, 1590, 574, 1562, 574, 5162, 4406, 4350, 578, 1562, 574, 522, 574, 1562, 574, 1590, 574, 494, 574, 522, 574, 1562, 578, 518, 574, 494, 578, 1586, 574, 494, 578, 518, 574, 1562, 578, 1586, 578, 494, 574, 1586, 578, 494, 602, 490, 578, 494, 574, 1590, 574, 1590, 574, 1562, 574, 1590, 574, 1562, 578, 1586, 574, 1590, 574, 1562, 578, 518, 578, 494, 574, 494, 574, 518, 578, 494, 574, 518, 578, 1562, 574, 1590, 574, 1590, 574, 1562, 574, 522, 574, 494, 574, 494, 602, 1562, 574, 522, 574, 494, 574, 494, 578, 518, 574, 1562, 578, 1586, 578, 1586, 574, 1000};

//For TV use: uint16_t rawData[RAW_DATA_LEN]={3454, 1738, 438, 434, 434, 1302, 438, 434, 438, 434, 434, 434, 462, 406, 438, 434, 434, 434, 438, 434, 434, 434, 438, 434, 434, 434, 438, 434, 434, 1302, 438, 434, 438, 434, 434, 434, 438, 430, 438, 434, 434, 434, 438, 434, 434, 434, 438, 434, 434, 1302, 438, 434, 438, 434, 434, 434, 438, 430, 438, 434, 462, 406, 462, 410, 434, 434, 466, 1274, 438, 434, 434, 1302, 438, 1302, 438, 1302, 438, 1302, 438, 434, 434, 434, 438, 1302, 438, 430, 438, 1302, 438, 1302, 438, 1302, 438, 1302, 438, 430, 438, 1302, 438, 1000};





/*
 * Cut-and-paste into the area above.
 */
   
void loop() {
  if (Serial.read() != -1) {
    //send a code every time a character is received from the 
    // serial port. You could modify this sketch to send when you
    // push a button connected to an digital input pin.
    mySender.send(rawData_1,RAW_DATA_LEN_1,38);//Pass the buffer,length, optionally frequency
    Serial.println(F("Sent signal."));
  }
}

