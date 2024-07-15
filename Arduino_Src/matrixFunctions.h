 /* Last Update 071424-02*/
 ArduinoLEDMatrix matrix;

 void matrixStatic(String matrixMsg){
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(matrixMsg);
  Serial.println(matrixMsg);
  matrix.endText();
  matrix.endDraw();
 }

 void matrixScroll(String matrixMsg2){
   matrix.beginDraw();
   matrix.stroke(0xFFFFFFFF);
   matrix.textScrollSpeed(50);
   matrix.textFont(Font_5x7);
   matrix.beginText(0, 1, 0xFFFFFF);
   matrix.println(matrixMsg2);
   Serial.println(matrixMsg2);
   matrix.endText(SCROLL_LEFT);
   matrix.endDraw();

 }

 void matrixLoad(){
  matrix.loadSequence(LEDMATRIX_ANIMATION_TETRIS);
  matrix.begin();
  matrix.play(false);
 }
