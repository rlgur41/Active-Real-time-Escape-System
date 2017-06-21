const int row[8] = {2, 7, 19, 5, 13, 18, 12, 16 };
const int col[8] = {6, 11, 10, 3, 17, 4, 8, 9 };

byte hex_left_upper[8] ={0xF8,0xF0,0xF0,0xF8,0x9C,0x0E,0x07,0x02};
byte hex_left_downer[8] ={0x02,0x07,0x0E,0x9C,0xF8,0xF0,0xF0,0xF8};
byte hex_right_upper[8] ={0x1F,0x0F,0x0F,0x1F,0x39,0x70,0xE0,0x40};
byte hex_right_downer[8] ={0x40,0xE0,0x70,0x39,0x1F,0x0F,0x0F,0x1F};

byte hex_up[8] ={0x18,0x3c,0x7e,0xff,0x18,0x18,0x18,0x18};
byte hex_down[8] ={0x18,0x18,0x18,0x18,0xff,0x7e,0x3c,0x18};


void Clear()
{
 for (int thisPin = 0; thisPin < 8; thisPin++)
 {
  digitalWrite(row[thisPin],LOW);
  digitalWrite(col[thisPin],HIGH);
 }
}
void LEFT_UP()
{
  for(int thisCol=0; thisCol<8; thisCol++)
  {
    Clear();      
    for(int thisRow=0; thisRow<8; thisRow++)
    {    
      byte light = (hex_right_upper[thisRow]&(0x01<<thisCol))>>thisCol;
      digitalWrite(row[thisRow],light);
    }
    digitalWrite(col[thisCol],LOW);    
    delay(1);
  }
  Clear();  
//  delay(500);
}
void LEFT_DOWN()
{
  for(int thisCol=0; thisCol<8; thisCol++)
  {
    Clear();      
    for(int thisRow=0; thisRow<8; thisRow++)
    {    
      byte light = (hex_right_downer[thisRow]&(0x01<<thisCol))>>thisCol;
      digitalWrite(row[thisRow],light);
    }
    digitalWrite(col[thisCol],LOW);    
    delay(1);
  }
  Clear();  
//  delay(500);
}
void RIGHT_UP()
{
  for(int thisCol=0; thisCol<8; thisCol++)
  {
    Clear();      
    for(int thisRow=0; thisRow<8; thisRow++)
    {    
      byte light = (hex_left_upper[thisRow]&(0x01<<thisCol))>>thisCol;
      digitalWrite(row[thisRow],light);
    }
    digitalWrite(col[thisCol],LOW);    
    delay(1);
  }
  Clear();  
//  delay(500);
}

void RIGHT_DOWN()
{
  for(int thisCol=0; thisCol<8; thisCol++)
  {
    Clear();      
    for(int thisRow=0; thisRow<8; thisRow++)
    {    
      byte light = (hex_left_downer[thisRow]&(0x01<<thisCol))>>thisCol;
      digitalWrite(row[thisRow],light);
    }
    digitalWrite(col[thisCol],LOW);    
    delay(1);
  }
  Clear();  
 // delay(500);

}
void UP()
{
  for(int thisCol=0; thisCol<8; thisCol++)
  {
    Clear();      
    for(int thisRow=0; thisRow<8; thisRow++)
    {    
      byte light = (hex_up[thisRow]&(0x01<<thisCol))>>thisCol;
      digitalWrite(row[thisRow],light);
    }
    digitalWrite(col[thisCol],LOW);    
    delay(1);
  }
  Clear();  
}
void DOWN()
{
  for(int thisCol=0; thisCol<8; thisCol++)
  {
    Clear();      
    for(int thisRow=0; thisRow<8; thisRow++)
    {    
      byte light = (hex_down[thisRow]&(0x01<<thisCol))>>thisCol;
      digitalWrite(row[thisRow],light);
    }
    digitalWrite(col[thisCol],LOW);
    delay(1);
  }
    Clear();  
}
void LEFT()
{
  for(int thisCol=0; thisCol<8; thisCol++)
  {
    Clear();      
    for(int thisRow=0; thisRow<8; thisRow++)
    {    
      byte light = (hex_up[thisCol]&(0x01<<thisRow))>>thisRow;
      digitalWrite(row[thisRow],light);
    }
    digitalWrite(col[thisCol],LOW);
    delay(1);
  }
    Clear();  
}
void RIGHT()
{
  for(int thisCol=0; thisCol<8; thisCol++)
  {
    Clear();      
    for(int thisRow=0; thisRow<8; thisRow++)
    {    
      byte light = (hex_down[thisCol]&(0x01<<thisRow))>>thisRow;
      digitalWrite(row[thisRow],light);
    }
    digitalWrite(col[thisCol],LOW);
    delay(1);
  }
    Clear();  
}


