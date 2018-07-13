/* rawSend.ino Example sketch for IRLib2
 *  Illustrates how to send a code Using raw timings which were captured
 *  from the "rawRecv.ino" sample sketch.  Load that sketch and
 *  capture the values. They will print in the serial monitor. Then you
 *  cut and paste that output into the appropriate section below.
 */
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender.
#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>

IRsendRaw mySender;
#define RAW_DATA_LEN 200

const PROGMEM uint16_t rawData_off[RAW_DATA_LEN]={4386, 4378, 550, 1586, 550, 546, 550, 1586, 550, 1614, 550, 522, 550, 542, 550, 1590, 550, 546, 546, 522, 550, 1614, 546, 522, 550, 546, 550, 1586, 550, 1614, 550, 518, 550, 1614, 550, 522, 546, 1618, 546, 1590, 550, 1614, 550, 1614, 550, 518, 550, 1614, 550, 1590, 546, 1618, 546, 522, 546, 550, 546, 522, 550, 546, 546, 1590, 550, 546, 538, 530, 550, 1614, 550, 1586, 550, 1614, 526, 546, 546, 550, 546, 522, 546, 546, 550, 522, 522, 570, 526, 546, 546, 522, 550, 1614, 522, 1642, 522, 1614, 526, 1638, 522, 1618, 522, 5210, 4382, 4382, 522, 1614, 522, 574, 522, 1614, 522, 1642, 522, 546, 526, 570, 522, 1618, 522, 570, 526, 546, 522, 1642, 522, 546, 522, 574, 522, 1614, 522, 1642, 522, 546, 522, 1642, 522, 550, 546, 1614, 526, 1638, 526, 1614, 522, 1642, 522, 546, 522, 1642, 522, 1614, 526, 1642, 522, 570, 522, 550, 522, 546, 522, 574, 522, 1614, 522, 574, 522, 546, 522, 1642, 522, 1642, 522, 1614, 522, 574, 522, 550, 518, 550, 522, 570, 522, 550, 522, 570, 522, 550, 522, 570, 522, 1618, 522, 1642, 522, 1614, 522, 1642, 522, 1642, 522, 1000};

const PROGMEM uint16_t rawData_on[RAW_DATA_LEN]={4382, 4374, 554, 1586, 550, 546, 550, 1586, 550, 1614, 550, 522, 550, 542, 550, 1590, 550, 546, 546, 522, 550, 1614, 550, 518, 550, 546, 550, 1586, 550, 1614, 550, 518, 550, 1614, 550, 522, 546, 546, 550, 522, 546, 1618, 546, 1590, 546, 1618, 550, 1614, 550, 1586, 550, 1614, 550, 1590, 546, 1618, 546, 522, 550, 546, 546, 522, 550, 546, 550, 518, 550, 546, 546, 1590, 550, 546, 550, 1586, 550, 1614, 526, 546, 546, 546, 526, 546, 546, 1618, 546, 522, 522, 1642, 522, 546, 522, 574, 522, 1614, 526, 1638, 522, 1618, 522, 5214, 4378, 4378, 526, 1614, 522, 574, 522, 1614, 522, 1642, 526, 546, 522, 570, 526, 1614, 522, 570, 526, 546, 522, 1642, 522, 546, 522, 574, 522, 1614, 522, 1642, 522, 546, 522, 1642, 522, 550, 546, 546, 522, 550, 522, 1638, 522, 1642, 522, 1618, 522, 1642, 522, 1614, 522, 1642, 522, 1642, 522, 1618, 522, 570, 526, 546, 522, 546, 522, 574, 522, 546, 522, 574, 522, 1614, 522, 574, 522, 1614, 522, 1642, 522, 550, 518, 574, 522, 550, 522, 1638, 522, 550, 522, 1642, 522, 546, 522, 574, 522, 1614, 522, 1642, 522, 1642, 522, 1000};

const PROGMEM uint16_t rawData_17[RAW_DATA_LEN]={4438, 4326, 578, 1558, 574, 522, 578, 1558, 554, 1610, 554, 518, 574, 518, 602, 1538, 574, 522, 598, 470, 550, 1614, 550, 518, 574, 522, 574, 1562, 574, 1590, 546, 522, 574, 1594, 566, 502, 570, 522, 550, 522, 546, 1618, 542, 1622, 570, 1566, 574, 1590, 574, 1566, 542, 1622, 574, 1562, 574, 1590, 574, 522, 574, 494, 574, 494, 578, 518, 574, 494, 550, 546, 550, 518, 578, 518, 574, 494, 550, 1614, 578, 494, 546, 546, 578, 494, 546, 1614, 578, 1562, 574, 1590, 574, 1562, 578, 518, 578, 1562, 546, 1618, 570, 1590, 578, 5162, 4378, 4354, 574, 1562, 578, 518, 550, 1614, 574, 1566, 550, 542, 578, 494, 574, 1590, 570, 498, 574, 494, 574, 1590, 574, 522, 550, 518, 550, 1614, 550, 1586, 574, 522, 578, 1562, 574, 522, 546, 522, 574, 518, 574, 1566, 546, 1618, 546, 1590, 574, 1590, 550, 1590, 574, 1590, 574, 1590, 570, 1566, 570, 526, 546, 522, 546, 550, 546, 526, 542, 522, 598, 498, 546, 526, 570, 522, 574, 498, 542, 1618, 546, 526, 542, 554, 542, 526, 542, 1622, 542, 1594, 546, 1618, 518, 1646, 546, 522, 546, 1618, 546, 1594, 566, 1598, 542, 1000};

const PROGMEM uint16_t rawData_18[RAW_DATA_LEN]={4410, 4350, 602, 1534, 602, 494, 602, 1534, 606, 1562, 602, 466, 574, 518, 578, 1562, 578, 518, 574, 494, 578, 1586, 602, 466, 578, 518, 578, 1558, 578, 1586, 578, 494, 574, 1590, 574, 494, 574, 522, 578, 490, 578, 1586, 602, 1562, 578, 1558, 578, 1586, 578, 1562, 574, 1590, 578, 1558, 578, 1586, 578, 518, 578, 490, 602, 470, 574, 518, 578, 494, 574, 518, 574, 494, 578, 518, 578, 1562, 574, 1590, 574, 494, 574, 522, 574, 494, 578, 1586, 578, 1558, 578, 1586, 578, 494, 574, 518, 554, 1586, 550, 1614, 578, 1586, 574, 5162, 4410, 4322, 578, 1562, 550, 542, 578, 1590, 574, 1562, 578, 518, 550, 518, 578, 1586, 550, 518, 578, 494, 574, 1586, 554, 542, 550, 518, 578, 1586, 578, 1562, 574, 522, 574, 1562, 578, 518, 574, 494, 550, 546, 574, 1562, 574, 1590, 550, 1590, 550, 1614, 574, 1562, 578, 1586, 550, 1614, 578, 1562, 574, 522, 574, 494, 550, 542, 554, 518, 574, 494, 602, 494, 550, 518, 574, 522, 550, 1586, 578, 1586, 578, 494, 550, 542, 550, 518, 578, 1586, 554, 1610, 550, 1590, 550, 546, 550, 518, 574, 1590, 550, 1586, 550, 1614, 550, 1000};

const PROGMEM uint16_t rawData_19[RAW_DATA_LEN]={4410, 4350, 554, 1586, 550, 546, 566, 1570, 550, 1614, 550, 518, 554, 542, 578, 1562, 550, 546, 546, 522, 550, 1614, 550, 518, 550, 546, 550, 1586, 550, 1614, 550, 518, 550, 1614, 550, 522, 550, 542, 550, 522, 550, 1614, 546, 1618, 546, 1590, 550, 1614, 550, 1586, 550, 1614, 578, 1562, 550, 1614, 550, 546, 550, 518, 566, 502, 550, 546, 550, 518, 550, 546, 550, 518, 550, 1614, 550, 1590, 550, 1614, 550, 518, 550, 546, 550, 518, 550, 1614, 574, 1562, 578, 518, 550, 522, 546, 546, 550, 1590, 546, 1618, 546, 1614, 550, 5190, 4354, 4378, 550, 1590, 546, 546, 550, 1614, 574, 1566, 550, 546, 546, 522, 550, 1614, 550, 518, 550, 518, 578, 1586, 550, 546, 578, 490, 550, 1614, 550, 1590, 550, 546, 546, 1590, 550, 546, 550, 518, 550, 546, 550, 1586, 550, 1614, 550, 1590, 546, 1618, 550, 1586, 574, 1590, 550, 1614, 550, 1590, 546, 546, 550, 522, 546, 546, 550, 522, 546, 522, 574, 522, 546, 522, 550, 1614, 546, 1618, 546, 1590, 550, 546, 550, 518, 550, 522, 574, 1590, 546, 1614, 550, 522, 546, 550, 546, 522, 546, 1618, 546, 1590, 550, 1614, 550, 1000};

const PROGMEM uint16_t rawData_20[RAW_DATA_LEN]={4358, 4402, 494, 1646, 518, 574, 522, 1618, 494, 1670, 494, 574, 498, 598, 494, 1642, 494, 602, 494, 574, 494, 1670, 494, 578, 494, 598, 494, 1646, 494, 1670, 494, 574, 494, 1670, 494, 574, 494, 602, 494, 574, 494, 1670, 494, 1670, 494, 1646, 494, 1670, 494, 1642, 494, 1670, 494, 1646, 494, 1670, 494, 598, 498, 574, 494, 574, 494, 602, 494, 574, 494, 602, 494, 574, 494, 1670, 494, 574, 494, 1670, 494, 574, 494, 602, 494, 574, 498, 1666, 494, 1646, 494, 602, 494, 1642, 494, 602, 494, 1642, 494, 1670, 494, 1670, 494, 5242, 4302, 4434, 494, 1642, 494, 602, 494, 1670, 494, 1642, 498, 598, 494, 578, 494, 1666, 498, 574, 494, 574, 522, 1642, 494, 602, 494, 574, 494, 1670, 494, 1642, 498, 598, 494, 1646, 494, 598, 498, 574, 494, 602, 494, 1642, 494, 1670, 494, 1642, 498, 1666, 498, 1642, 518, 1646, 494, 1670, 494, 1642, 494, 602, 494, 574, 494, 602, 494, 578, 490, 578, 518, 574, 494, 578, 494, 1670, 494, 574, 494, 1670, 494, 574, 494, 602, 494, 574, 494, 1670, 494, 1670, 494, 574, 494, 1670, 494, 578, 494, 1666, 498, 1642, 494, 1670, 494, 1000};

const PROGMEM uint16_t rawData_21[RAW_DATA_LEN]={4402, 4358, 570, 1566, 546, 550, 570, 1566, 570, 1594, 570, 502, 570, 526, 570, 1566, 570, 526, 570, 498, 570, 1594, 570, 498, 570, 526, 570, 1570, 570, 1590, 574, 498, 570, 1594, 570, 498, 570, 526, 570, 498, 570, 1594, 570, 1594, 570, 1566, 574, 1590, 574, 1566, 570, 1594, 570, 1566, 574, 1590, 574, 522, 570, 498, 574, 498, 570, 522, 574, 498, 570, 522, 574, 1566, 570, 1594, 570, 498, 570, 1594, 574, 494, 574, 522, 570, 498, 574, 1590, 574, 498, 570, 522, 574, 1566, 570, 526, 570, 1566, 574, 1590, 570, 1594, 570, 5166, 4378, 4354, 574, 1566, 574, 522, 570, 1594, 570, 1566, 574, 522, 570, 498, 574, 1590, 574, 498, 570, 498, 598, 1566, 570, 522, 574, 498, 570, 1594, 570, 1566, 574, 522, 570, 1566, 574, 522, 574, 494, 574, 522, 574, 1562, 574, 1594, 570, 1566, 574, 1590, 574, 1566, 598, 1562, 574, 1590, 574, 1566, 574, 522, 570, 498, 570, 526, 570, 498, 570, 498, 598, 498, 570, 1594, 570, 1566, 574, 522, 570, 1570, 570, 522, 574, 498, 570, 498, 598, 1566, 570, 526, 570, 498, 570, 1594, 570, 498, 570, 1594, 574, 1566, 562, 1602, 570, 1000};

const PROGMEM uint16_t rawData_22[RAW_DATA_LEN]={4402, 4358, 570, 1566, 570, 526, 570, 1570, 570, 1590, 574, 498, 570, 526, 570, 1566, 570, 526, 570, 498, 570, 1594, 570, 498, 570, 526, 570, 1570, 570, 1590, 574, 498, 570, 1594, 570, 498, 570, 526, 570, 498, 570, 1594, 570, 1594, 570, 1566, 574, 1590, 574, 1566, 570, 1594, 570, 1566, 574, 1590, 574, 522, 570, 498, 574, 498, 570, 522, 574, 498, 570, 522, 574, 1566, 570, 1594, 570, 1594, 570, 1566, 574, 522, 570, 498, 574, 498, 570, 1590, 574, 498, 598, 498, 570, 498, 570, 526, 570, 1566, 570, 1594, 570, 1594, 570, 5166, 4378, 4354, 574, 1566, 570, 526, 570, 1594, 570, 1566, 574, 522, 570, 498, 574, 1590, 574, 494, 574, 498, 598, 1566, 570, 526, 570, 498, 570, 1594, 570, 1566, 574, 522, 570, 1566, 574, 522, 574, 494, 574, 522, 574, 1566, 570, 1590, 574, 1566, 570, 1594, 570, 1570, 598, 1562, 574, 1590, 574, 1566, 570, 526, 570, 498, 570, 526, 570, 498, 570, 498, 598, 498, 570, 1594, 570, 1566, 574, 1590, 574, 1566, 570, 526, 570, 498, 570, 526, 570, 1566, 550, 546, 570, 498, 570, 526, 566, 502, 574, 1590, 546, 1590, 550, 1618, 570, 1000};

const PROGMEM uint16_t rawData_23[RAW_DATA_LEN]={4402, 4358, 570, 1570, 570, 522, 570, 1570, 570, 1594, 570, 498, 570, 526, 570, 1566, 570, 526, 570, 498, 570, 1594, 570, 502, 570, 522, 570, 1570, 570, 1594, 570, 498, 570, 1594, 570, 498, 570, 526, 570, 498, 570, 1594, 570, 1594, 570, 1570, 570, 1594, 570, 1566, 570, 1594, 570, 1570, 570, 1594, 570, 522, 574, 498, 570, 498, 570, 526, 570, 498, 570, 526, 570, 1566, 570, 526, 570, 1566, 574, 1590, 574, 494, 574, 522, 574, 498, 570, 1590, 574, 498, 570, 1594, 570, 498, 570, 526, 570, 1566, 574, 1590, 574, 1590, 574, 5162, 4378, 4354, 574, 1566, 574, 522, 570, 1594, 570, 1566, 574, 522, 574, 494, 574, 1590, 574, 498, 570, 498, 598, 1566, 570, 526, 570, 498, 570, 1594, 570, 1566, 574, 522, 574, 1566, 570, 522, 574, 498, 570, 522, 574, 1566, 570, 1594, 570, 1566, 574, 1590, 574, 1566, 598, 1566, 570, 1594, 570, 1566, 574, 522, 570, 498, 574, 522, 570, 498, 574, 494, 598, 498, 574, 1590, 574, 494, 574, 1590, 574, 1566, 570, 526, 570, 498, 570, 498, 598, 1566, 574, 522, 570, 1566, 574, 522, 574, 494, 574, 1590, 574, 1566, 570, 1594, 570, 1000};

const PROGMEM uint16_t rawData_24[RAW_DATA_LEN]={4562, 4198, 570, 1566, 546, 550, 570, 1566, 570, 1594, 546, 526, 570, 522, 570, 1570, 570, 526, 570, 498, 570, 1594, 570, 498, 570, 526, 570, 1566, 574, 1590, 570, 502, 570, 1590, 574, 498, 570, 526, 570, 498, 570, 1594, 570, 1594, 570, 1566, 574, 1590, 570, 1570, 570, 1594, 570, 1566, 570, 1594, 570, 526, 570, 498, 570, 502, 570, 522, 574, 498, 570, 522, 574, 1566, 570, 522, 574, 498, 570, 1594, 570, 498, 570, 526, 570, 498, 570, 1594, 570, 498, 574, 1590, 570, 1570, 570, 522, 574, 1566, 570, 1594, 570, 1594, 570, 5166, 4378, 4354, 574, 1566, 570, 526, 570, 1590, 574, 1566, 570, 526, 570, 498, 570, 1594, 574, 494, 574, 498, 598, 1566, 570, 522, 574, 498, 570, 1594, 570, 1566, 570, 526, 570, 1566, 574, 522, 570, 498, 574, 522, 570, 1566, 574, 1590, 574, 1566, 570, 1594, 570, 1566, 598, 1566, 574, 1590, 574, 1566, 570, 526, 570, 498, 570, 526, 570, 498, 570, 498, 598, 498, 570, 1594, 570, 498, 574, 494, 574, 1590, 574, 498, 570, 522, 574, 498, 570, 1590, 574, 498, 570, 1594, 570, 1594, 570, 498, 574, 1590, 570, 1566, 574, 1590, 574, 1000};

const PROGMEM uint16_t rawData_25[RAW_DATA_LEN]={4378, 4382, 546, 1594, 542, 554, 542, 1594, 542, 1622, 542, 530, 542, 550, 542, 1598, 542, 550, 546, 526, 542, 1622, 542, 526, 542, 554, 542, 1594, 542, 1622, 542, 526, 546, 1618, 546, 526, 542, 550, 546, 526, 542, 1622, 542, 1618, 546, 1594, 542, 1622, 542, 1594, 546, 1618, 546, 1594, 542, 1622, 542, 554, 542, 526, 542, 526, 546, 550, 542, 526, 546, 1618, 546, 1590, 574, 526, 542, 526, 542, 1618, 546, 526, 542, 554, 566, 502, 566, 530, 542, 526, 570, 1594, 546, 1590, 546, 550, 546, 1594, 566, 1598, 542, 1618, 546, 5190, 4542, 4194, 546, 1590, 546, 550, 570, 1594, 546, 1594, 570, 526, 542, 526, 542, 1622, 570, 498, 570, 498, 598, 1566, 546, 550, 570, 498, 570, 1594, 546, 1594, 566, 526, 570, 1570, 570, 526, 570, 498, 570, 526, 570, 1566, 570, 1594, 570, 1570, 570, 1594, 566, 1570, 594, 1570, 570, 1594, 546, 1590, 570, 526, 570, 502, 566, 526, 570, 502, 570, 498, 594, 1570, 570, 1594, 570, 498, 570, 526, 570, 1566, 570, 526, 570, 498, 570, 502, 594, 498, 570, 502, 570, 1590, 574, 1590, 574, 498, 570, 1594, 570, 1566, 570, 1594, 570, 1000};

const PROGMEM uint16_t rawData_26[RAW_DATA_LEN]={4326, 4434, 494, 1642, 498, 598, 494, 1646, 494, 1670, 494, 574, 494, 602, 494, 1642, 494, 602, 494, 574, 494, 1670, 494, 578, 494, 598, 494, 1646, 494, 1670, 494, 574, 494, 1670, 494, 574, 494, 602, 494, 574, 494, 1670, 494, 1670, 494, 1646, 494, 1670, 494, 1642, 494, 1670, 494, 1646, 494, 1670, 494, 598, 494, 578, 494, 574, 494, 602, 494, 574, 494, 1670, 494, 1642, 522, 574, 494, 1670, 494, 1642, 498, 602, 490, 578, 494, 574, 494, 602, 494, 574, 494, 1670, 494, 574, 494, 602, 494, 1642, 494, 1670, 494, 1670, 494, 5242, 4302, 4434, 494, 1642, 494, 602, 494, 1670, 494, 1642, 498, 598, 494, 574, 498, 1666, 498, 574, 494, 574, 522, 1642, 494, 602, 494, 574, 494, 1670, 494, 1642, 494, 602, 494, 1646, 494, 598, 498, 574, 494, 598, 494, 1646, 494, 1670, 494, 1642, 494, 1670, 494, 1646, 518, 1646, 494, 1670, 494, 1642, 494, 602, 494, 574, 494, 602, 494, 574, 494, 578, 518, 1642, 498, 1666, 498, 574, 494, 1670, 494, 1642, 494, 602, 494, 574, 494, 602, 494, 574, 494, 602, 494, 1642, 498, 598, 494, 574, 498, 1666, 498, 1642, 494, 1670, 494, 1000};

const PROGMEM uint16_t rawData_27[RAW_DATA_LEN]={4402, 4358, 570, 1566, 570, 526, 570, 1566, 570, 1594, 570, 502, 570, 522, 570, 1570, 570, 526, 570, 498, 570, 1594, 570, 498, 570, 526, 570, 1566, 570, 1594, 570, 502, 570, 1594, 570, 498, 570, 526, 570, 498, 570, 1594, 570, 1594, 570, 1566, 570, 1594, 570, 1570, 570, 1594, 570, 1566, 570, 1594, 570, 526, 570, 498, 570, 498, 574, 522, 570, 502, 570, 1590, 574, 498, 570, 522, 574, 1566, 570, 1594, 570, 498, 570, 526, 570, 498, 570, 526, 570, 1566, 570, 1594, 574, 498, 570, 522, 574, 1566, 570, 1594, 570, 1594, 570, 5166, 4378, 4354, 570, 1570, 570, 526, 570, 1594, 570, 1566, 570, 526, 570, 498, 570, 1594, 570, 498, 570, 502, 594, 1570, 570, 522, 570, 502, 570, 1590, 574, 1566, 570, 526, 570, 1566, 570, 526, 570, 498, 570, 526, 570, 1566, 574, 1590, 574, 1566, 570, 1594, 570, 1566, 598, 1566, 574, 1590, 574, 1566, 570, 526, 570, 498, 570, 526, 570, 498, 570, 498, 598, 1566, 570, 526, 570, 498, 570, 1594, 570, 1570, 570, 522, 574, 498, 570, 498, 598, 498, 570, 1594, 570, 1566, 570, 526, 570, 498, 570, 1594, 570, 1570, 570, 1594, 570, 1000};

const PROGMEM uint16_t rawData_28[RAW_DATA_LEN]={4402, 4358, 570, 1570, 570, 526, 566, 1570, 570, 1594, 570, 498, 570, 526, 570, 1566, 570, 526, 570, 498, 570, 1594, 570, 502, 570, 522, 570, 1570, 570, 1594, 570, 498, 570, 1594, 570, 498, 570, 526, 570, 498, 570, 1594, 574, 1590, 570, 1570, 570, 1594, 570, 1566, 570, 1594, 570, 1570, 570, 1594, 570, 522, 574, 498, 570, 498, 570, 526, 570, 498, 570, 1594, 570, 498, 570, 526, 570, 498, 570, 1594, 570, 498, 574, 522, 570, 498, 574, 522, 570, 1570, 570, 1590, 574, 1566, 570, 526, 570, 1566, 570, 1594, 574, 1590, 574, 5162, 4378, 4358, 570, 1566, 574, 522, 570, 1594, 570, 1570, 570, 522, 574, 498, 570, 1590, 574, 498, 570, 498, 598, 1566, 570, 526, 570, 498, 570, 1594, 570, 1566, 574, 522, 574, 1566, 570, 526, 570, 498, 570, 522, 574, 1566, 570, 1594, 570, 1570, 570, 1590, 574, 1566, 598, 1566, 570, 1594, 570, 1566, 574, 522, 570, 498, 574, 522, 574, 494, 574, 498, 598, 1562, 574, 522, 574, 498, 570, 498, 570, 1594, 570, 498, 570, 526, 570, 498, 570, 526, 570, 1566, 574, 1590, 574, 1590, 574, 494, 574, 1594, 570, 1566, 570, 1594, 570, 1000};

const PROGMEM uint16_t rawData_29[RAW_DATA_LEN]={4410, 4350, 578, 1562, 578, 518, 602, 1534, 602, 1562, 578, 490, 602, 494, 550, 1586, 578, 518, 578, 494, 602, 1558, 578, 494, 602, 494, 550, 1586, 550, 1614, 574, 494, 602, 1562, 578, 494, 598, 494, 550, 518, 578, 1586, 554, 1610, 554, 1586, 602, 1562, 578, 1558, 578, 1586, 554, 1586, 574, 1590, 602, 494, 550, 518, 574, 494, 602, 494, 550, 518, 578, 1586, 578, 490, 554, 1610, 578, 494, 598, 1566, 574, 494, 550, 546, 574, 494, 602, 494, 574, 1562, 550, 546, 574, 1562, 578, 518, 578, 1562, 574, 1586, 578, 1590, 550, 5182, 4386, 4350, 574, 1562, 578, 518, 578, 1586, 574, 1566, 574, 522, 574, 494, 574, 1590, 574, 494, 578, 490, 578, 1586, 578, 518, 550, 518, 578, 1586, 550, 1590, 550, 546, 574, 1562, 574, 522, 550, 518, 578, 518, 574, 1562, 578, 1586, 550, 1590, 574, 1590, 574, 1562, 602, 1562, 574, 1590, 578, 1562, 550, 546, 546, 522, 574, 522, 574, 494, 574, 494, 602, 1562, 550, 546, 574, 1562, 574, 522, 574, 1562, 574, 522, 578, 490, 578, 494, 574, 518, 578, 1586, 550, 522, 550, 1614, 546, 522, 574, 1590, 574, 1562, 566, 1598, 574, 1000};

const PROGMEM uint16_t rawData_30[RAW_DATA_LEN]={4586, 4174, 570, 1566, 570, 526, 570, 1566, 546, 1618, 570, 502, 570, 526, 570, 1566, 570, 526, 570, 498, 570, 1594, 570, 498, 570, 526, 570, 1566, 574, 1594, 566, 502, 570, 1594, 570, 498, 570, 526, 570, 498, 570, 1594, 570, 1594, 570, 1566, 570, 1594, 570, 1570, 570, 1594, 570, 1566, 574, 1590, 570, 526, 570, 498, 574, 498, 570, 522, 574, 498, 570, 1594, 570, 498, 570, 1594, 570, 1594, 570, 1566, 574, 522, 570, 498, 574, 498, 570, 522, 574, 1566, 598, 498, 570, 498, 570, 526, 570, 1566, 570, 1594, 570, 1594, 570, 5166, 4530, 4206, 570, 1566, 570, 526, 570, 1594, 570, 1566, 570, 526, 570, 498, 574, 1590, 574, 494, 574, 498, 598, 1566, 570, 526, 570, 498, 570, 1594, 570, 1566, 570, 526, 570, 1566, 574, 522, 574, 494, 574, 522, 574, 1566, 570, 1594, 570, 1566, 574, 1590, 574, 1566, 594, 1566, 574, 1594, 570, 1566, 570, 526, 570, 498, 570, 526, 570, 498, 574, 498, 594, 1566, 574, 522, 574, 1566, 570, 1590, 574, 1566, 570, 526, 570, 498, 570, 526, 570, 498, 570, 1594, 570, 498, 574, 522, 570, 498, 574, 1590, 574, 1566, 570, 1594, 570, 1000};

uint16_t RAW[RAW_DATA_LEN];
/*
 * Cut-and-paste into the area above.
 */

void buffcopy(uint16_t * src, uint16_t * dst, int len) {
    for (byte i=0;i<len;i++) 
    {
      dst[i]=pgm_read_word_near(src + i);
      //Serial.println(dst[i]);
    }
}
#define MODBUS 1
#ifdef MODBUS
//MODBUS CODE
modbusDevice regBank;
modbusSlave slave;
void setup()
{   

//Assign the modbus device ID.  
  regBank.setId(4);
  regBank.add(40001); //Recives command here
  regBank.add(40002); //Saves result here
  

/*
Assign the modbus device object to the protocol handler
This is where the protocol handler will look to read and write
register data.  Currently, a modbus slave protocol handler may
only have one device assigned to it.
*/
  slave._device = &regBank;  

// Initialize the serial port for coms at 9600 baud  
  slave.setBaud(19200);    
  regBank.set(40001,0);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{ int cmd;
  uint16_t *src;
  while(1)
  {
     if (slave.run())
     {
          cmd=regBank.get(40001);
          
          byte cmd_valid=1;
          if(cmd==1) src=rawData_off;       //1 for off and 
          else if (cmd==2) src=rawData_on;  //2 for on
          else if(cmd==17) src=rawData_17;
          else if(cmd==18) src=rawData_18;
          else if(cmd==19) src=rawData_19;
          else if(cmd==20) src=rawData_20;
          else if(cmd==21) src=rawData_21;
          else if(cmd==22) src=rawData_22;
          else if(cmd==23) src=rawData_23;
          else if(cmd==24) src=rawData_24;
          else if(cmd==25) src=rawData_25;
          else if(cmd==26) src=rawData_26;
          else if(cmd==27) src=rawData_27;
          else if(cmd==28) src=rawData_28;
          else if(cmd==29) src=rawData_29;
          else if(cmd==30) src=rawData_30;
          else cmd_valid=0;
          if(cmd_valid)
            {
              
              buffcopy(src,RAW,RAW_DATA_LEN);
              mySender.send(RAW,RAW_DATA_LEN,38);//Pass the buffer,length, optionally frequency

              for(int i=0; i<cmd; i++)
                { digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
                delay(150);                       // wait for a second
                digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
                delay(150);
                //Just an indicator. Comment to eliminate delay.
                }
            }
                    
     }
   }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#else

void setup() {
  Serial.begin(19200);
  delay(1000); while (!Serial); //delay for Leonardo
  Serial.println(F("Every time you press a key is a serial monitor we will send."));
}




String readline()
{
  
  String cmd="";
  char rcv;
  
  
  while (Serial.available())Serial.read();
  while(!Serial.available());
  delay(10);
  
  do
  {
    rcv=Serial.read();
    
    if(rcv!='\n' && rcv!='\r')
    cmd+=rcv;
  }while(rcv!='\n');

  Serial.println("Rcvd CMD: " + cmd);
  
  return cmd;
}
   
void loop() {

  
  String cmd=readline();
  uint16_t *src;
  byte cmd_valid=1;
  if(cmd=="off") src=rawData_off;  
  else if (cmd=="on") src=rawData_on;
  else if(cmd=="t17") src=rawData_17;
  else if(cmd=="t18") src=rawData_18;
  else if(cmd=="t19") src=rawData_19;
  else if(cmd=="t20") src=rawData_20;
  else if(cmd=="t21") src=rawData_21;
  else if(cmd=="t22") src=rawData_22;
  else if(cmd=="t23") src=rawData_23;
  else if(cmd=="t24") src=rawData_24;
  else if(cmd=="t25") src=rawData_25;
  else if(cmd=="t26") src=rawData_26;
  else if(cmd=="t27") src=rawData_27;
  else if(cmd=="t28") src=rawData_28;
  else if(cmd=="t29") src=rawData_29;
  else if(cmd=="t30") src=rawData_30;
  else cmd_valid=0;

  if(cmd_valid)
  {
    Serial.println("Valid CMD: " + cmd);
    buffcopy(src,RAW,RAW_DATA_LEN);
    mySender.send(RAW,RAW_DATA_LEN,38);//Pass the buffer,length, optionally frequency
  }
  

  
}

#endif


