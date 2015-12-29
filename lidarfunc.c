#include "lidarfunc.h"

//extern  send function for your thingamajig ?

int lidarParser(byte readByte)
{

  //static promenljive inicijalizuju se samo jednom
  //tako da ovaj deo mozete ignorisati sem za prvi put
	static struct lidarStruct data;//inicijalizuj data bice 0 zbog static 
	static data_state dataState = SYNC;  //package state bolje
	static byteorder byteOrder = LOW;
	static int i = 0; //data loop
	static int j = 0; //data loop

	int dist; //temp distance from data
	int angle;

  switch (dataState)
  {

    // start byte 0xFA
    case SYNC:    
      if (readByte == 0xFA)
        {
          data.start = 0xFA;
          dataState = INDEX;
        }
      else
        {
          dataState = SYNC;  
        }
    break;

    // index 1 byte from 0xA0 to 0xF9
    case INDEX:
      if ((readByte >= 0xA0) && (readByte <= 0xF9))
        {
          data.index = readByte - 0xA0;
          dataState = MSPEED;
        }
      else
        {
          dataState = SYNC;
          byteOrder = LOW;
        }
    break;
    //motor speed 2 bajta
    case MSPEED:
        //lower byte
        if (byteOrder == LOW){
          data.mspeedL = readByte;
          byteOrder = HIGH;
    break;
        }
        //higher byte
        if (byteOrder == HIGH){
          data.mspeedH = readByte;
          dataState = DATA;
          //init za prijem podataka 
          i = 0;
          j = 0;
          byteOrder = LOW;
    break;
        }
        //ovde ne sme uci 

    //podatci 4 bajta
    case DATA:
        //stavi petlju
        data.data[i][j] = readByte;
        j++;
        //ovo lepse napisi
        if (j == 4) {  
          i++;
          j = 0;
        }
        if(i == 4){
          dataState = CSUM;
        }
    break;

    //checksum 2 byte
    case CSUM:
    
        if (byteOrder == LOW){
          data.csuml = readByte;
          byteOrder = HIGH;
        }
        //higher byte
        if (byteOrder == HIGH){
          data.mspeedH = readByte;
          dataState = DATA;
          i = 0;
          j = 0;
          byteOrder = LOW;
        }
      dataState = SYNC; //package done
      for(i=0;i<4;i++)
            {
             
            dist = ((0x3f & data.data[i][1]) << 8) | data.data[i][0];
            angle = (data.index * 4) + i;
            /*OVDE USLOVI ZA ZA SLANJE (DA LI JE ISPUNJENO)*/
            /*OVDE POZIV ZA SPI SEND */
            //ILI DA bude vracena struktura 
            

            struct dist_angl_t
            {
              int dist[4];
              int angle; //ili angle[4]

            }
      }
      i=0;
return 1;
}