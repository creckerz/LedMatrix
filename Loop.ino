
bool MenuOpen = false;
//---------------------------------------------------------loop()---------------------------------------------------------
void loop() {                                                           //Clear all leds from last frame
  if(irrecv.decode(&results)){
    Remote();
  }
  if(MenuOpen){
    showMenu();
  }else{
    if(Mode != 2){
      leds.clear();  
      snakeStarted = false;
      TimerMoveSnake.end();
      
      level[0] =  fft.read(0);
      level[1] =  fft.read(1);
      level[2] =  fft.read(2, 3);
      level[3] =  fft.read(4, 6);
      level[4] =  fft.read(7, 10);
      level[5] =  fft.read(11, 15);
      level[6] =  fft.read(16, 22);
      level[7] =  fft.read(23, 32);
      level[8] =  fft.read(33, 46);
      level[9] =  fft.read(47, 66);
      level[10] = fft.read(67, 93);
      level[11] = fft.read(94, 131);
      level[12] = fft.read(132, 184);
      level[13] = fft.read(185, 257);
      level[14] = fft.read(258, 359);
      level[15] = fft.read(360, 511);
    }else if (Mode == 2){
      
      level[0] =  fft.read(1,20);
      int colorHead = (int)(level[0]*scale)%15;
      leds.setPixel(getMI(snakePos[0][0], snakePos[0][1]), colors[colorpicker][colorHead] );
    }
    switch (Mode){
      case 0:
        ClassicVisualization();
        break;
      case 1:
        MidVisualization();
        break;
      case 2:
        if(!snakeStarted){
          dirR = true;
          snakeStarted = true;
          SnakeStart();
        }
        break;
    }
  }
  
  leds.show();                                                              //Update matrix
}
//--------------------------------------------------------/loop()---------------------------------------------------------
