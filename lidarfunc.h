//lidarfunc.h

typedef enum data_state {SYNC,INDEX,POSITION,MSPEED,DATA,CSUM};
typedef enum byteorder {LOW,HIGH};

typedef unsigned char byte;

typedef struct lidarStruct
  {
    byte start;
    byte index;
    byte mspeedL;
    byte mspeedH;
    byte data[4][4];
    byte csuml;
    byte csumh;
  };