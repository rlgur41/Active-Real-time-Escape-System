#include <XBee.h>

XBee xbee = XBee();

ZBRxResponse zbRx = ZBRxResponse(); 
XBeeResponse response = XBeeResponse();
ModemStatusResponse msr = ModemStatusResponse();
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

void data_send(ZBTxRequest& zbTx)
{ 
  boolean retry = true; // retry 변수, 만약 보낸 대상으로부터 ACK(제대로 받았는지 확인)이 날라오지 않으면 다시 보내기 위함
  while(retry == true){    
      xbee.send(zbTx); // 데이터 전송
      
      if (xbee.readPacket(500)) { // ACK를 받음           
        if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) { // 오 데이터 들어옴 굿굿
          xbee.getResponse().getZBTxStatusResponse(txStatus); // txStatus에 성공 여부를 저장

          if (txStatus.getDeliveryStatus() == SUCCESS) { // 50byte를 읽음, txStatus에 ACK이 정상적으로 날라왔다면 SUCCESS 매크로가 들어옴.
              Serial.println("[OK] Send Success"); // 보내기 성공
              retry = false; // 정상적으로 보냈으니 반복해서 보낼 필요 없음
          } else {
              Serial.println("[FAIL] Send Fail"); // ㅈ댐;; 안갔음
              retry = true; // 다시 보내보쟈
              continue; // while로 가서 다시 send 실행
          }
        }
     } 
    else {
        Serial.println("FAIL] Unknown Error"); // 이게 뭔 에러당가;; 알수음슴
    }
  }
}

static int inf = 99; // 무한대 값

//=============0==============
//===1=========2==========3===
//===4=========5==========6===

uint8_t printPath(int historyPath[], int _start, int _end);


uint8_t dikstra(int graph[][7], int _start) 
{
      int re[]={4,5,6};
      int num=0;
      int sh = 4;
      int vCount = 7; // 정점의 수
      boolean isVisits[vCount];
      int distance[vCount]; // 거리배열
      int historyPath[vCount]; // 히스토리 배열
 
        int nextVertex = _start; // distance 배열의 최소값의 정점
        int _min = 0; // distance 배열의 최소값
        // 초기화
        for (int i = 0; i < vCount; i++) {
            isVisits[i] = false; // 방문 한 곳 없다고 초기화
            distance[i] = inf; // 전부 다 무한대로 초기화
            historyPath[i] = inf; // 전부 다 무한대로 초기화
        }
        distance[_start] = 0; // 시작점 0 으로 초기화
 
        // 다익스트라 실행
        while (true) {
            _min = inf; // 최소값을 infinity 초기화
            for (int j = 0; j < vCount; j++) {
                if (isVisits[j] == false && distance[j] < _min) { // 가장 먼저 방문했던
                                                                    // 노드는 제외한다,
                                                                    // 또한 최소값을
                                                                    // 찾기위한
                                                                    // 조사(선택정렬을
                                                                    // 생각하면 된다.)
                    nextVertex = j; // 다음으로 이동할 정점 선택
                    _min = distance[j]; // 다음으로 이동한 최소값
                }
            }
            if (_min == inf)
                break; // 최소값이 infinity이면 모든 정점을 지났다는 것, 최소값이 모든 정점을 지났으면
                        // infinity
            isVisits[nextVertex] = true; // 다음으로 이동할 정점 방문
 
            for (int j = 0; j < vCount; j++) {
                int distanceVertex = distance[nextVertex]
                        + graph[nextVertex][j]; // 정점에서 방문한 다른 정점의 거리
                if (distance[j] > distanceVertex) // 정점에서 다른 정점에서의 거리가 distance
                                                    // 배열보다 적다면 교체해 준다.
                {
                    distance[j] = distanceVertex; // 교체해 준다.
                    historyPath[j] = nextVertex; // 교체 된다면 그 지점의 정점을 기록을 남긴다.
                }
            }
        }
        for(int i = 0; i< (sizeof(re) / sizeof(int)) - 1; i++){
      //  sh = re[i];
        if(distance[re[i]] > distance[re[i+1]])
          sh = re[i+1];
        }     

        return printPath(historyPath, _start, sh );
      
}

static int stack_trace = 0;

volatile static int stack[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

boolean isEmpty()
{
  if(stack_trace <= 0){
    return true;
  }
  return false;
}

int pop()
{
  if(!isEmpty()){
    return stack[--stack_trace];
  }

  return -1; //never happend
}
void push(int data)
{
  stack[stack_trace++] = data;  
}
uint8_t printPath(int historyPath[], int _start, int _end) { // 경로계산
        int vertex = _end; // 거꾸로 탐색한다.
        while (true) {
            push(vertex);
            if (vertex == _start)
                break; // 시작점이면 리턴한다.
            vertex = historyPath[vertex]; // 탐색
        }

        int idx;
        if(stack_trace == 1){
          idx = stack_trace-1;
        }
        else {
          idx = stack_trace-2;
        }

        uint8_t ret = stack[idx] + '0';
  
        Serial.print(_start);
        Serial.print("-> ");
        Serial.print(_end);
        Serial.print(" path is : ");
       while (!isEmpty()){
      
           Serial.print(pop());
           Serial.print(" ");
       }
        Serial.println("");
        return ret;     
    }





uint8_t set_path(int fire[], int fire_size, int __st){
  int weightMatrix[][7] = {
                //  0    1    2    3    4    5    6
        /* 0 */ {   0,   1,   1,   1,   inf, inf,inf},
        /* 1 */ {   1,   0,   2,  inf,   1, inf, inf},
        /* 2 */ {   1,   1,   0,   1, inf,   1, inf},
        /* 3 */ {   1,   inf,   2,   0,  inf,   inf,   1},
        /* 4 */ {  inf,   1, inf,  inf,   0, 2,   inf},
        /* 5 */ {  inf , inf,   1,   inf, 2,   0, 2},
        /* 6 */ {  inf, inf, inf,   1,   inf, 2,   0}
        };

  int st = __st;
  int count = fire_size;

  
  for(int i = 0; i<count; i++){
         if(fire[i] == 0){
            for(int j = 0; j<6; j++){
             weightMatrix[0][j] = inf;
              weightMatrix[j][0] = inf;
            }
          }
          if(fire[i] == 1){
            for(int j = 0; j<6; j++){
            weightMatrix[1][j] = inf;
            weightMatrix[j][1] = inf;
            }
          }
          if(fire[i] == 2){
            for(int j = 0; j<6; j++){
            weightMatrix[2][j] = inf;
            weightMatrix[j][2] = inf;
            }
          }
          if(fire[i] == 3){
            for(int j = 0; j<6; j++){
            weightMatrix[3][j] = inf;
            weightMatrix[j][3] = inf;
            }
          }
          if(fire[i] == 4){
            for(int j = 0; j<6; j++){
            weightMatrix[4][j] = inf;
            weightMatrix[j][4] = inf;
            }
          }
          if(fire[i] == 5){
            for(int j = 0; j<6; j++){
            weightMatrix[5][j] = inf;
            weightMatrix[j][5] = inf;
            }
          }
          if(fire[i] == 6){
            for(int j = 0; j<6; j++){
            weightMatrix[6][j] = inf;
            weightMatrix[j][6] = inf;
         }
       }
   }
   return dikstra(weightMatrix, __st); 
}


//=============0==============
//===1=========2==========3===
//===4=========5==========6===

XBeeAddress64 addr_form[6] = { XBeeAddress64(0x0013a200, 0x415B6612), // 2-1
                               XBeeAddress64(0x0013a200, 0x415B663E), // 2-2
                               XBeeAddress64(0x0013a200, 0x415B6631), // 2-3
                               XBeeAddress64(0x0013a200, 0x415B663D), // 4
                               XBeeAddress64(0x0013a200, 0x415B660F), // 5
                               XBeeAddress64(0x0013a200, 0x415B667A) }; // 6

ZBTxRequest tx_form[6];



