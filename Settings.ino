//-------------------------------------------------lightDimmer()/ISR--------------------------------------------------
void lightDimmer(){
  TimerMoveSnake.end();
  brightnes += 4;
  if(brightnes > 16)
    brightnes = 1;
  generateColors();
    
}
//-------------------------------------------------lightDimmer()/ISR--------------------------------------------------

//-------------------------------------------------colorPickerNext()/ISR--------------------------------------------------
void colorPickerNext(){
  TimerMoveSnake.end();
  colorpicker++;                                                            //Increment color counter
  if(colorpicker >= ColorCount){                                            //Reset color counter if higher than n(colors)
    colorpicker = 0;
    }
}
//------------------------------------------------/colorPickerNext()/ISR--------------------------------------------------

//-------------------------------------------------colorPickerNext()/ISR--------------------------------------------------
void colorModeNext(){
  TimerMoveSnake.end();
  colorMode++;                                                            //Next colormode
  if(colorMode > allColorModes){                                                      //Reset colormode if higher than n(colormodes)
    colorMode = 0;
  }
}
//------------------------------------------------/colorPickerNext()/ISR--------------------------------------------------

//-------------------------------------------------ModePickerNext()/ISR--------------------------------------------------
void ModePickerNext(){
  TimerMoveSnake.end();
  Mode++;                                                            //Increment color counter
  if(Mode >= AllModes){                                            //Reset color counter if higher than n(colors)
    Mode = 0;
    }
}
//------------------------------------------------/ModePickerNext()/ISR--------------------------------------------------
