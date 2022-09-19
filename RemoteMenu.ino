unsigned long lastPressed;

unsigned long zero = 0x1CE300FF;
unsigned long one = 0x1CE3807F;
unsigned long two = 0x1CE340BF;
unsigned long three = 0x1CE3C03F;
unsigned long four = 0x1CE320DF;
unsigned long five = 0x1CE3A05F;
unsigned long six = 0x1CE3609F;
unsigned long seven = 0x1CE3E01F;
unsigned long eight = 0x1CE310EF;
unsigned long nine = 0x1CE3906F;


unsigned long arrowUp = 0x1CE350AF;
unsigned long arrowDown = 0x1CE3D02F;
unsigned long arrowLeft = 0x1CE3F00F;
unsigned long arrowRight = 0x1CE3708F;
unsigned long confirm = 0x1CE330CF;

unsigned long Menu = 0x1CE3E817;

int MenuShow = 0;
int RGBNr = 0;
int RL = 255, RR = 255, GL = 255, GR = 255, BL = 255, BR = 255;
int RGBArray[3];
int inputcount = 0;
#define MaxMenu 5

void Remote(){
  if(Mode == 2){
    snakeMovement(); //GOTO "Snake"
  }
  if(results.value == Menu){
    showMenu();
  }
  if(MenuOpen){
    if(results.value == arrowDown || (results.value == 0xFFFFFF && lastPressed == arrowDown)){
      MenuShow++;
      if(MenuShow >= MaxMenu) MenuShow = 0;
    }else if(results.value == arrowRight|| (results.value == 0xFFFFFF && lastPressed == arrowRight)){
      if(MenuShow == 0){
        Mode++;
        if(Mode >= AllModes){
          Mode = 0;
        }
      }else if(MenuShow == 1){
        RGBNr++;
        if(RGBNr >= 6){
          RGBNr = 0;
        }
      }else if(MenuShow == 2){
          colorMode++;
          if(colorMode >= allColorModes){
            colorMode = 0;
          }
        }else if(MenuShow == 3){
            brightnes += 4;
            if(brightnes > 17)
              brightnes = 1;
            generateColors();
        }else if(MenuShow == 4){
            scale += 4;
            if(scale > 256)
              scale = 4;
        }
    }else if(results.value == arrowUp|| (results.value == 0xFFFFFF && lastPressed == arrowUp)){
      MenuShow--;
      if(MenuShow < 0) MenuShow = MaxMenu - 1;
    }else if(results.value == arrowLeft|| (results.value == 0xFFFFFF && lastPressed == arrowLeft)){
      if(MenuShow == 0){
        Mode--;
        if(Mode < 0){
          Mode = AllModes-1;
        }
      }else if(MenuShow == 1){
          RGBNr--;
        if(RGBNr < 0){
          RGBNr = 5;
        }
       }else if(MenuShow == 2){
          colorMode--;
          if(colorMode < 0){
            colorMode = allColorModes;
          }
        }else if(MenuShow == 3){
            brightnes -= 4;
            if(brightnes < 1)
              brightnes = 17;
            generateColors();
        }else if(MenuShow == 4){
            scale -= 4;
            if(scale < 4)
              scale = 256;
        }
    }else if(results.value == confirm|| (results.value == 0xFFFFFF && lastPressed == confirm)){
      MenuOpen = false;
    }
    if(MenuShow == 1){
      checkInput();
      if(inputcount > 2){
        switch(RGBNr){
          case(0):
            RL = loadInRGB();
            break;
          case(1):
            GL = loadInRGB();
            break;
          case(2):
            BL = loadInRGB();
            break;
          case(3):
            RR = loadInRGB();
            break;
          case(4):
            GR = loadInRGB();
            break;
          case(5):
            BR = loadInRGB();
            break;
        }
        replaceRGB(RL, GL, BL, RR, GR, BR, 2);
        generateColors();
        leds.clear();
        colorpicker = 2;
      }
    }
  }
  Serial.print("0x");
  Serial.println(results.value, HEX);
  irrecv.resume(); // Restart the ISR state machine and Receive the next value
  if(results.value != 0xFFFFFFFF){
    lastPressed = results.value;
  }
}

int loadInRGB(){
  int finalVal = RGBArray[0]*100 + RGBArray[1]*10 + RGBArray[2];
  if(finalVal > 255) finalVal = 255;
  inputcount = 0;
  return finalVal;
}

void checkInput(){
  if(results.value == zero){
    RGBArray[inputcount++] = 0;
  }
  if(results.value == one){
    RGBArray[inputcount++] = 1;
  }
  if(results.value == two){
    RGBArray[inputcount++] = 2;
  }
  if(results.value == three){
    RGBArray[inputcount++] = 3;
  }
  if(results.value == four){
    RGBArray[inputcount++] = 4;
  }
  if(results.value == five){
    RGBArray[inputcount++] = 5;
  }
  if(results.value == six){
    RGBArray[inputcount++] = 6;
  }
  if(results.value == seven){
    RGBArray[inputcount++] = 7;
  }
  if(results.value == eight){
    RGBArray[inputcount++] = 8;
  }
  if(results.value == nine){
    RGBArray[inputcount++] = 9;
  }
}

void showMenu(){
  MenuOpen = true;
  TimerMoveSnake.end();
  leds.clear();  
  if(MenuShow == 0){
    M(0,0); O(6,0); D(11,0);
    number(Mode, 5, 10);
  }else if(MenuShow == 1){
    C(0,0); O(4,0); L(9,0);
    if(RGBNr == 0){
      int index1 = RL/100; int index2 = (RL - index1*100)/10; int index3 = RL - index1*100 - index2*10;
      R(0, 10); number(1,13,0); number(index1,4,10); number(index2,8,10); number(index3,12,10);}
    if(RGBNr == 1){
      int index1 = GL/100; int index2 = (GL - index1*100)/10; int index3 = GL - index1*100 - index2*10;
      G(0, 10); number(1,13,0); number(index1,4,10); number(index2,8,10); number(index3,12,10);}
    if(RGBNr == 2){
      int index1 = BL/100; int index2 = (BL - index1*100)/10; int index3 = BL - index1*100 - index2*10;
      B(0, 10); number(1,13,0); number(index1,4,10); number(index2,8,10); number(index3,12,10);}
    
    if(RGBNr == 3){
      int index1 = RR/100; int index2 = (RR - index1*100)/10; int index3 = RR - index1*100 - index2*10;
      R(0, 10); number(2,12,0); number(index1,4,10); number(index2,8,10); number(index3,12,10);}
    if(RGBNr == 4){
      int index1 = GR/100; int index2 = (GR - index1*100)/10; int index3 = GR - index1*100 - index2*10;
      G(0, 10); number(2,12,0); number(index1,4,10); number(index2,8,10); number(index3,12,10);}
    if(RGBNr == 5){
      int index1 = BR/100; int index2 = (BR - index1*100)/10; int index3 = BR - index1*100 - index2*10;
      B(0, 10); number(2,12,0); number(index1,4,10); number(index2,8,10); number(index3,12,10);}
  }else if(MenuShow == 2){
    M(0,0); O(6,0); D(11,0);
    C(0,8); O(4,8); L(9,8);
    number(colorMode,12,8);
  }else if(MenuShow == 3){
    B(0,0); R(6,0); I(11,0);
    int index1 = brightnes/10; int index2 = brightnes - index1*10;
    number(index1,0,8);  number(index2,5,8);
  }else if(MenuShow == 4){
    S(0,0); C(4,0); A(9,0); L(13,0);
      int index1 = scale/100; int index2 = (scale - index1*100)/10; int index3 = scale - index1*100 - index2*10;
      number(index1,0,10); number(index2,4,10); number(index3,9,10);
  }
  leds.show();
}
