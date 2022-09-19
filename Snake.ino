
void snakeMovement(){
    if(results.value == arrowDown || (results.value == 0xFFFFFF && lastPressed == arrowDown)){
      MoveDown();
    }else if(results.value == arrowRight|| (results.value == 0xFFFFFF && lastPressed == arrowRight)){
      MoveRight();
    }else if(results.value == arrowUp|| (results.value == 0xFFFFFF && lastPressed == arrowUp)){
      MoveUp();
    }else if(results.value == arrowLeft|| (results.value == 0xFFFFFF && lastPressed == arrowLeft)){
      MoveLeft();
    }
}

void MoveLeft(){
  if(!dirR){
    dirU = false;
    dirR = false;
    dirL = true;
    dirD = false;
  }
}
void MoveUp(){
  if(!dirD){
    dirU = true;
    dirR = false;
    dirL = false;
    dirD = false;
  }
}
void MoveDown(){
  if(!dirU){
    dirU = false;
    dirR = false;
    dirL = false;
    dirD = true;
  }
}
void MoveRight(){
  if(!dirL){
    dirU = false;
    dirR = true;
    dirL = false;
    dirD = false;
  }
}

//--------------------------------------------------------/Snake()---------------------------------------------------------
void SnakeStart(){
  TimerMoveSnake.begin(SnakeMove, 200000);
  leds.clear();  
  dirR = true;
  dirL = false;
  dirU = false;
  dirD = false;
  snakeLength = 2;
  snakePos[1][0] = 1;   snakeHeadTail[1][0] = snakePos[1][0];
  
  snakePos[1][1] = 1;  snakeHeadTail[1][1] = snakePos[1][1];
  snakePos[0][0] = 2;   snakeHeadTail[0][0] = snakePos[0][0];
  snakePos[0][1] = 1;  snakeHeadTail[0][1] = snakePos[0][1];
  for(int i = 0; i < sizeof(snakePos); i++){
      leds.setPixel(getMI(snakePos[i][0], snakePos[i][1]), colors[colorpicker][0] );
  }
  seed[0] = random(0, 15);
  seed[1] = random(0, 15);
  leds.setPixel(getMI(seed[0], seed[1]), colors[0][15] );
  
  leds.show();
}
bool eatenSeed = false;


void SnakeMove(){
  leds.clear();
  leds.setPixel(getMI(seed[0], seed[1]), colors[colorpicker][seed[0]]);                        //the Seed to get
  //Check the selected Direction
  if(dirR){
    snakeHeadTail[0][0] += 1;
  }else if(dirL){
    snakeHeadTail[0][0] -= 1;
  }else if(dirU){
    snakeHeadTail[0][1] -= 1;
  }else if(dirD){
    snakeHeadTail[0][1] += 1;
  }
  //walk trough wall
  if(snakeHeadTail[0][0] == 16 && snakeHeadTail[0][1] == snakePos[0][1])
    snakeHeadTail[0][0] = 0;
  else if(snakeHeadTail[0][0] == -1 && snakeHeadTail[0][1] == snakePos[0][1])
    snakeHeadTail[0][0] = 15;
  if(snakeHeadTail[0][1] == 16 && snakeHeadTail[0][0] == snakePos[0][0])
    snakeHeadTail[0][1] = 0;
  else if(snakeHeadTail[0][1] == -1 && snakeHeadTail[0][0] == snakePos[0][0])
    snakeHeadTail[0][1] = 15;
    
  for(int i = 0; i < snakeLength; i++){
      if(snakeHeadTail[0][0] == snakePos[i][0] && snakeHeadTail[0][1] == snakePos[i][1]){
        SnakeStart();
        return;
    }
  }
  //Move one Step
  for(int i = snakeLength; i > 0 ; i--){
    snakePos[i][0] = snakePos[i-1][0];
    snakePos[i][1] = snakePos[i-1][1];
    leds.setPixel(getMI(snakePos[i][0], snakePos[i][1]), colors[colorpicker][(snakeLength-i)%15] );
    if(seed[0] == snakePos[i][0] && seed[1] == snakePos[i][1]){
      seed[0] = random(0, 15);
      seed[1] = random(0, 15);
      leds.setPixel(getMI(seed[0], seed[1]), colors[colorpicker][seed[0]] );
      eatenSeed = true;
    }
  }
  if(eatenSeed){
    snakeLength++;
    eatenSeed = false;
  }
  snakePos[0][0] = snakeHeadTail[0][0]; snakePos[0][1] = snakeHeadTail[0][1];
  leds.show();
}
//--------------------------------------------------------/Snake()---------------------------------------------------------
