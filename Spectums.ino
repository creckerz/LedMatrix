//--------------------------------------------------------/ClassicVisualization()---------------------------------------------------------
void ClassicVisualization(){
  for(int i = 0; i < matrix_width; i++){                                    //Iterate through all bands/columns of matrix
    int val = level[i] * scale;                                             //Scale signal to match height of matrix
    if(val >= matrix_height) val = matrix_height;                           //Max value = matrix height

    if(val >= shown[i]){                                                    //Smooth decay of level
      shown[i] = val;
    }else{
      if(shown[i] > 0) shown[i] = shown[i] - 1;
      val = shown[i];
    }
      
    if(shown[i] >= 0){
      for(int z = 0; z < val; z++){                                         //Draw all pixels below value (= Bar)
        switch (colorMode){
          case 0:
            leds.setPixel(getMI(i, (matrix_height) - val + z), colors[colorpicker][i] );
            break;
          case 1:
            leds.setPixel(getMI(i, (matrix_height) - val + z), colors[colorpicker][val - z - 1] );
            break;
          case 2:
            leds.setPixel(getMI(i, (matrix_height) - val + z), colors[colorpicker][z]);
            break;
          case 3:
            leds.setPixel(getMI(i, (matrix_height) - val + z), colors[colorpicker][matrix_width - 1 - i] );
            break;
          case 4:
            leds.setPixel(getMI(i, (matrix_height) - val + z), colors[colorpicker][matrix_height - val + z] );
            break;
          case 5:
            leds.setPixel(getMI(i, (matrix_height) - val + z), colors[colorpicker][matrix_height - 1 - z] );
            break;
        }
      }
    }
  }  
}
//--------------------------------------------------------/ClassicVisualization()---------------------------------------------------------

//--------------------------------------------------------/MidVisualization()---------------------------------------------------------
void MidVisualization(){
  
  for(int i = 0; i < matrix_width; i++){                                    //Iterate through all bands/columns of matrix
    int val = level[i] * scale;                                             //Scale signal to match height of matrix
    if(val >= matrix_height/2) val = matrix_height/2;                       //Max value = matrix height

    if(val >= shown[i]){                                                    //Smooth decay of level
      shown[i] = val;
    }else{
      if(shown[i] > 0) shown[i] = shown[i] - 1;
      val = shown[i];
    }
      
    if(shown[i] >= 0){
      for(int z = 0; z < val; z++){                                         //Draw all pixels below value (= Bar)
        switch (colorMode){
          case 0:
            leds.setPixel(getMI(i, (matrix_height/2) - val + z), colors[colorpicker][i] );
            leds.setPixel(getMI(i, (matrix_height/2 - 1) + val - z), colors[colorpicker][i] );
            break;
          case 1:
            leds.setPixel(getMI(i, (matrix_height/2) - val + z), colors[colorpicker][val - z - 1] );
            leds.setPixel(getMI(i, (matrix_height/2 - 1) + val - z), colors[colorpicker][val - z - 1] );
            break;
          case 2:
            leds.setPixel(getMI(i, (matrix_height/2) - val + z), colors[colorpicker][z] );
            leds.setPixel(getMI(i, (matrix_height/2 - 1) + val - z), colors[colorpicker][z] );
            break;
          case 3:
            leds.setPixel(getMI(i, (matrix_height/2) - val + z), colors[colorpicker][matrix_width - 1 - i] );
            leds.setPixel(getMI(i, (matrix_height/2 - 1) + val - z), colors[colorpicker][matrix_width - 1 - i] );
            break;
          case 4:
            leds.setPixel(getMI(i, (matrix_height/2) - val + z), colors[colorpicker][matrix_height - val + z] );
            leds.setPixel(getMI(i, (matrix_height/2 - 1) + val - z), colors[colorpicker][matrix_height - val + z] );
            break;
          case 5:
            leds.setPixel(getMI(i, (matrix_height/2) - val + z), colors[colorpicker][matrix_height - 1 - z] );
            leds.setPixel(getMI(i, (matrix_height/2 - 1) + val - z), colors[colorpicker][matrix_height - 1 - z] );
            break;
        }
      }
    }
  }
}
//--------------------------------------------------------/MidVisualization()---------------------------------------------------------

//--------------------------------------------------------getMI()---------------------------------------------------------
int getMI(int x, int y) {                                                   //Calculate LED number from x and y(matrix)
  if ((x & 1) == 0) {                                                       
    return x * matrix_width + matrix_width - 1 - y;
  }else{
    return x * matrix_width + y;
  }
}
//-------------------------------------------------------/getMI()---------------------------------------------------------
