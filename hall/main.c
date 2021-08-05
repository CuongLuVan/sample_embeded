
#include <msp430.h>
#define RADIO_MODE_TX  1
#define RADIO_MODE_RX  2
static char data[64],radioMode;



static void preparePacket(char id, char* data, char* length)
{
    char i;
    static char payloadLength;

    payloadLength++;
    if (payloadLength > 254)
        payloadLength = 1;

    // First byte of packet contains the length of the payload
    data[0] = payloadLength;

    // First byte of payload contains an id
    data[1] = id;

    // Fill rest of packet with dummy data
    for (i = 2; i <= payloadLength; i++)
        data[i] = i;

    // Packet length is payload + length byte
    *length = payloadLength + 1;
}


//----------------------------------------------------------------------------------
//  void main(void)
//
//  DESCRIPTION:
//    This is the main entry of the "link_interrupt" application. It sets up the board
//    and lets the user select operating mode (RX or TX) by pressing either button
//    S1 or S2. In TX mode, a packet containing random data (with arbitrary length)
//    is written to the FIFO of the RF chip continously. In RX mode, the LCD will be
//    updated every time a new packet is successfully received. If an error occurs
//    during reception, a LED will flash.
//----------------------------------------------------------------------------------

void Mcu_chipInit(void)
{
    WDTCTL = WDTPW + WDTHOLD;
      P1DIR=0xf0;
      P1SEL =0xf0;//HAL_SPI_SOMI_PIN);
      P1SEL&=~BIT4;
      P1DIR&=~BIT4;//HAL_SPI_SOMI_PIN);
         // MCU_IO_INPUT(HAL_SPI_SOMI_PORT, HAL_SPI_SOMI_PIN);
        P1SEL&=~BIT2;     //MCU_IO_OUTPUT(HAL_SPI_SIMO_PORT, HAL_SPI_SIMO_PIN, 0);
          P1OUT|=BIT2;
          P1DIR&=~BIT2;
          // MCU_IO_OUTPUT(HAL_SPI_CLK_PORT,  HAL_SPI_CLK_PIN, 0);
           // MCU_IO_OUTPUT(HAL_SPI_CS_PORT, HAL_SPI_CS_PIN, 1);
           
           
           
           
    // Keep peripheral in reset state
    UCA0CTL1 = UCSWRST;
UCA0CTL1 |= UCSSEL_2; 
    // 8-bit SPI Master 3-pin mode, with SMCLK as clock source
    UCA0CTL0  = UCCKPH + UCMSB + UCMST + UCSYNC;
    UCA0CTL1 |= UCSSEL1 + UCSSEL0;

    // Ignore clockrate argument for now, just use clock source/2
    UCA0BR0 = 0x02;
    UCA0BR1 = 0x00;

    // Set up pins used by peripheral unit
   P1SEL|=BIT1; // MCU_IO_PERIPHERAL(HAL_SPI_SOMI_PORT, HAL_SPI_SOMI_PIN);
   P1SEL|=BIT2;//MCU_IO_PERIPHERAL(HAL_SPI_SIMO_PORT, HAL_SPI_SIMO_PIN);
   P1SEL|=BIT3;// MCU_IO_PERIPHERAL(HAL_SPI_CLK_PORT,  HAL_SPI_CLK_PIN);
   P1SEL&=~BIT0;        /// MCU_IO_OUTPUT(HAL_SPI_CS_PORT, HAL_SPI_CS_PIN, 1);

    // Release for operation
    UCA0CTL1 &= ~UCSWRST;
     __enable_interrupt();
     
     
     
     
     
     
     
    UCA0CTL1 |= UCSWRST;               // Keep USCI in reset state
    UCA0CTL1 |= UCSSEL_2;              // SMCLK
    UCA0BR0  = 0x22;                   // 4MHz 115200
    UCA0BR1  = 0x00;                   // 4MHz 115200
    UCA0MCTL = 0x08;                   // 4Mhz Modulation
    
    // Set up pins used by peripheral unit (USCI_A0)
   // P1SEL |= BIT4;    // P2.4 = TXD

    UCA0CTL1 &= ~UCSWRST;              // Initialize USCI state machine
    
     __enable_interrupt();

}
void halUartWrite(const char* buf, int length)
{
    int i;
    for(i = 0; i < length; i++)
    {
        while (!(IFG2 & UCA0TXIFG));   // Wait for TX buffer ready to receive new byte
        UCA0TXBUF = buf[i];            // Output character
    }
}
void halRfResetChip(void)
{//chua dich het
    // Toggle chip select signal
      P1OUT|=BIT0;  //  HAL_SPI_CS_DEASSERT;
     _delay_cycles(120); //  halMcuWaitUs(30);
     P1OUT&=~BIT0;  // MCU_IO_CLR HAL_SPI_CS_ASSERT;
     _delay_cycles(120);
     P1OUT|=BIT0;  // HAL_SPI_CS_DEASSERT;
     _delay_cycles(150);

    // Send SRES command
    P1OUT&=~BIT0;  // HAL_SPI_CS_ASSERT;
          while(P1IN&BIT1); //  while(HAL_SPI_SOMI_VAL);
       UCA0TXBUF=  0x30;  //HAL_SPI_TXBUF = (x);HAL_SPI_TXBUF_SET(CC2500_SRES);
    while (!(IFG2&UCA0TXIFG));                //   while(!(U0TCTL & TXEPT));// HAL_SPI_WAIT_TXFIN;

    // Wait for chip to finish internal reset
        while(P1IN&BIT1); //  while (HAL_SPI_SOMI_VAL);
    P1OUT|=BIT0; // HAL_SPI_CS_DEASSERT;
}

char halSpiRead(char addr, char* data, int length)
{
    int i;
    char rc;

   // HAL_SPI_BEGIN;
  P1OUT&=~BIT0;//  HAL_SPI_CS_ASSERT; 
  while(P1IN&BIT1); // while(HAL_SPI_SOMI_VAL);
   
//#ifdef HAL_SPI_INTERFACE_BITBANG
   // rc = halSpiBitbangOut(addr);
   // for (i = 0; i < length; i++)
  //  {
      //  data[i] = halSpiBitbangIn();
   // }
//#else
   UCA0TXBUF=addr;//  HAL_SPI_TXBUF_SET(addr);
  while (!(IFG2&UCA0TXIFG));//  HAL_SPI_WAIT_TXFIN;
    rc =UCA0RXBUF;// HAL_SPI_RXBUF;
    for (i = 0; i < length; i++)
    {
        UCA0TXBUF=0;// HAL_SPI_TXBUF_SET(0);        // Dummy write to read data byte
    while (!(IFG2&UCA0TXIFG));//   HAL_SPI_WAIT_TXFIN;
        data[i] = UCA0RXIE;//HAL_SPI_RXBUF;     // Store data from last data RX
    }
//#endif
     P1OUT|=BIT0; // HAL_SPI_END;
    return(rc);
}


char halRfReadStatusReg(char addr)
{
    char reg;
    halSpiRead(addr | 0xc0, &reg, 1);
    return(reg);
}


 char halRfGetChipId(void){
 
 
    return(halRfReadStatusReg(0x30));
 }




char halRfGetChipVer(void)
{
    return(halRfReadStatusReg(0x31));
}

char halSpiStrobe(char cmd)
{
    char rc;

   P1OUT&=~BIT0;//  HAL_SPI_BEGIN;
//#ifdef HAL_SPI_INTERFACE_BITBANG
 //   rc = halSpiBitbangOut(cmd);
//#else
     UCA0TXBUF=cmd;// HAL_SPI_TXBUF_SET(cmd);
      while (!(IFG2&UCA0TXIFG));// HAL_SPI_WAIT_TXFIN;
    rc = UCA0RXBUF;
//#endif
     P1OUT|=BIT0; // HAL_SPI_END;
    return(rc);
}

char halRfStrobe(char cmd)
{
    return(halSpiStrobe(cmd));
}





//----------------------------------------------------------------------------------
//  Function declarations
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//  uint8 rxRecvPacket(uint8* data, uint8* length)
//
//  DESCRIPTION:
//    Receive a packet that is smaller than the size of the FIFO, i.e. wait for the
//    complete packet to be received before reading from the FIFO. This function sets
//    the CC1100/CC2500 in RX and waits for the chip to signal that a packet is received.
//
//  ARGUMENTS:
//    data   - Where to write incoming data.
//    length - Length of payload.
//
//  RETURNS:
//    0 if a packet was received successfully.
//    1 if chip is in overflow state (packet longer than FIFO).
//    2 if the length of the packet is illegal (0 or > 61).
//    3 if the CRC of the packet is not OK.
//----------------------------------------------------------------------------------
static char rxRecvPacket(char* data, char* length)
{
    char packet_status[2];
    char status;
    //uint16 key;

   // packetReceived = FALSE;
 status = 0xff;

    // Set radio in RX mode
    halRfStrobe(0x34);

    // Wait for incoming packet
   // key = halIntLock();
  //  while(!packetReceived)
   // {
     //   halMcuSetLowPowerMode(HAL_MCU_LPM_3);
    //    key = halIntLock();
   // }
  //  halIntUnlock(key);

    // Read first element of packet from the RX FIFO
 //   status = halRfReadFifo(length, 1);

  //  if ((status & 0x70) == 0x60)
  //  {
        halRfStrobe(0x3a);
        halRfStrobe(0x37);
    //    status = RX_FIFO_OVERFLOW;
   // }
   // else if (*length == 0 || *length > 61)
   // {
    //    halRfStrobe(CC2500_SIDLE);
     //   halRfStrobe(CC2500_SFRX);
    //    status = RX_LENGTH_VIOLATION;
   // }
  //  else
   // {
        // Get payload
      //  halRfReadFifo(data, *length);

        // Get the packet status bytes [RSSI, LQI]
       // halRfReadFifo(packet_status, 2);

        // Check CRC
       // if ((packet_status[1] & CC2500_LQI_CRC_OK_BM) != CC2500_LQI_CRC_OK_BM)
       // {
     //       status = RX_CRC_MISMATCH;
       // }
       // else
       /// {
          //  status = RX_OK;
       // }
  //  }
    return(status);
}



//----------------------------------------------------------------------------------
//  void myRxButtonISR(void)
//
//  DESCRIPTION:
//    This function is called when the S1 button is pressed.
//    Selects mode of operation the first time it runs.
//----------------------------------------------------------------------------------
/*static void myRxButtonISR(void)
{
    if (!radioModeSet)
    {
        radioMode = RADIO_MODE_RX;
        radioModeSet = TRUE;
     //   halLcdWriteSymbol(HAL_LCD_SYMBOL_ANT, TRUE);
     //   halLcdWriteSymbol(HAL_LCD_SYMBOL_RX, TRUE);
    }
    buttonPushed = TRUE;
}
*/
//----------------------------------------------------------------------------------
//  void myTxButtonISR(void)
//
//  DESCRIPTION:
//    This function is called when the S2 button is pressed.
//    Selects mode of operation the first time it runs.
//----------------------------------------------------------------------------------
/*static void myTxButtonISR(void)
{
    if (!radioModeSet)
    {
        radioMode = RADIO_MODE_TX;
        radioModeSet = TRUE;
     //   halLcdWriteSymbol(HAL_LCD_SYMBOL_ANT, TRUE);
  //      halLcdWriteSymbol(HAL_LCD_SYMBOL_TX, TRUE);
    }
    buttonPushed = TRUE;
}
*/
//----------------------------------------------------------------------------------
//  void preparePacket(uint8 id, uint8* data, uint8* length)
//
//  DESCRIPTION:
//    Set up a dummy packet, where the first byte contains the length of the payload
//    and the first byte of the payload contains a packet id.
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//  uint8 rxRecvPacket(uint8* data, uint8* length)
//
//  DESCRIPTION:
//    Receive a packet that is smaller than the size of the FIFO, i.e. wait for the
//    complete packet to be received before reading from the FIFO. This function sets
//    the CC1100/CC2500 in RX and waits for the chip to signal that a packet is received.
//
//  ARGUMENTS:
//    data   - Where to write incoming data.
//    length - Length of payload.
//
//  RETURNS:
//    0 if a packet was received successfully.
//    1 if chip is in overflow state (packet longer than FIFO).
//    2 if the length of the packet is illegal (0 or > 61).
//    3 if the CRC of the packet is not OK.
//----------------------------------------------------
void main (void)
{
char  id;
char  ver;
   // uint16 key;
  //  halBoardInit();
Mcu_chipInit();
    halUartWrite("CC1100 & CC2500 Link Example\r\n", 30);
    halRfResetChip();
    id  = halRfGetChipId();
   ver = halRfGetChipVer();
    //halLcdWriteValue((id << 8) | ver, HAL_LCD_RADIX_HEX, 0);

    // Put radio to sleep
    halRfStrobe(0x39);


    // Set up interrupts for events on the S1 and S2 buttons
  //  halDigioIntSetEdge(&pinS1, HAL_DIGIO_INT_RISING_EDGE);
  //  halDigioIntConnect(&pinS1, &myRxButtonISR);
    //halDigioIntEnable(&pinS1);

   // halDigioIntSetEdge(&pinS2, HAL_DIGIO_INT_RISING_EDGE);
 //   halDigioIntConnect(&pinS2, &myTxButtonISR);
  //  halDigioIntEnable(&pinS2);

    // Wait for user to select operating mode
    /*key = halIntLock();
    while (!buttonPushed)
    {
        halMcuSetLowPowerMode(HAL_MCU_LPM_3);
        key = halIntLock();
    }
    halIntUnlock(key);
    buttonPushed = FALSE;
*/
    // Setup chip with register settings from SmartRF Studio
   // halRfConfig(&myRfConfig, myPaTable, myPaTableLen);

    // Additional chip configuration for this example
   halRfWriteReg(0x18,    0x18);   // Calibration from IDLE to TX/RX
    halRfWriteReg(0x17,    0x00);   // No CCA, IDLE after TX and RX
    halRfWriteReg(0x08, 0x45);   // Enable data whitening and CRC
    halRfWriteReg(0x07, 0x04);   // Enable append mode
    halRfWriteReg(0x02,   0x06);   // Set GDO0 to be packet received signal


    // In this example, the packets being sent are smaller than the size of the
    // FIFO, thus all larger packets should be discarded. The packet length
    // filtering on the receiver side is necessary in order to handle the
    // CC2500 RX FIFO overflow errata, described in the CC2500 Errata Note.
    // Given a FIFO size of 64, the maximum packet is set such that the FIFO
    // has room for the length byte + payload + 2 appended status bytes (giving
    // a maximum payload size of 64 - 1 - 2 = 61.
    halRfWriteReg(0x06, 61);   // Max payload data length



    if (radioMode == RADIO_MODE_RX)
    {
      //  uint16 counter;
      //  uint8 payloadLength;

        // Connect RX interrupt to event on GDO0
      //  halDigioIntSetEdge(&pinGDO0, HAL_DIGIO_INT_FALLING_EDGE);
     //   halDigioIntConnect(&pinGDO0, &rxISR);
       // halDigioIntEnable(&pinGDO0);

       // counter = 0;
        while (1)
        {
         //   if (rxRecvPacket(data, &payloadLength) == 0)
            {
         //       halLcdWriteValue(++counter, HAL_LCD_RADIX_HEX, 0);
            }
          ///  else
            {
              //  halLedToggle(1);
             //   halMcuWaitUs(20000);
               // halLedToggle(1);
            }
        }
    }
    else if (radioMode == RADIO_MODE_TX)
    {
       // uint16 counter;
        //uint8 packetLength;

        // Connect TX interrupt to event on GDO0
       // halDigioIntSetEdge(&pinGDO0, HAL_DIGIO_INT_FALLING_EDGE);
      //  halDigioIntConnect(&pinGDO0, &txISR);
      //  halDigioIntEnable(&pinGDO0);

        //counter = 0;
        while (1)
        {
            // Create a dummy packet
         //   preparePacket(counter, data, &packetLength);

            // Send packet
          ///  txSendPacket(data, packetLength);

            // Display number of packets sent
          //  halLcdWriteValue(++counter, HAL_LCD_RADIX_HEX, 0);

            // Wait for user to press button to continue
         //   key = halIntLock();
           // while (!buttonPushed)
           // {
              /// halMcuSetLowPowerMode(HAL_MCU_LPM_3);
              //  key = halIntLock();
           // }
          //  halIntUnlock(key);
           // buttonPushed = FALSE;
        }
    }
}


