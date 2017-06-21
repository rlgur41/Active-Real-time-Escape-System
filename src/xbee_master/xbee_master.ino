#include <mthread.h>
//#include <XBee.h>

// Our custom Thread:
class FooThread : public Thread
{
public:
    FooThread(int id);
protected:
    bool loop();
private:
    int id;
};
 
FooThread::FooThread(int id)
{
    this->id = id;
}
 
bool FooThread::loop()
{
 
    // Die if requested:
    if(kill_flag)
        return false;
 
    // Print the status message:
    Serial.print("FooThread ");
    Serial.print(id);
    Serial.println(" called.");
 
    // Sleep for one second:
    sleep(1);
    return true;
 
}
 
void setup()
{
 
    // Create five threads and add them to the main ThreadList:
    for(int i = 1; i <= 5; i++)
        main_thread_list->add_thread(new FooThread(i));
 
    // Initialize the serial connection:
    Serial.begin(9600);
    delay(1000);
 
}

/*#define ADDR_SH 0x0013a200    // All Nodes have a same SH address
#define ADDR_L  0x415B6631    // Left Node
#define ADDR_R  0x415B663D    // Right Node
#define ADDR_U  0x415B667A    // Under Node

XBee xbee = XBee();

struct addr_list
{
  XBeeAddress64 remoteAddress_l;
  XBeeAddress64 remoteAddress_r;
  XBeeAddress64 remoteAddress_u;
}addr_list;


void setup () 
{
  Serial.begin(9600);
  xbee.begin(Serial);
  
  addr_list.remoteAddress_l = XBeeAddress64(ADDR_SH, ADDR_L);
  addr_list.remoteAddress_r = XBeeAddress64(ADDR_SH, ADDR_R);
  addr_list.remoteAddress_u = XBeeAddress64(ADDR_SH, ADDR_U);
}


uint8_t text1[] = {'4', '1', '5', 'B', '6', '6', '3', '1'};
uint8_t text2[] = {'4', '1', '5', 'B', '6', '6', '3', 'D'};
uint8_t text3[] = {'4', '1', '5', 'B', '6', '6', '7', 'A'};


// XBeeAddress64 remoteAddress3 = XBeeAddress64(0x0013a200, 0x415B663E);

static void sender(void* arg)
{
  pinMode(2, INPUT_PULLUP);
  
  while(1){
    if(digitalRead(2) == LOW){
      send_message(addr_list.remoteAddress_l, text1);
      send_message(addr_list.remoteAddress_r, text2);
      send_message(addr_list.remoteAddress_u, text3);
    }  
  }
}

static void receiver(void* arg)
{
  uint8_t msg[50];
  read_message();
}
/*void loop () 
{
  send_message(addr_list.remoteAddress_l, text1);
  delay(1000);
}*/

