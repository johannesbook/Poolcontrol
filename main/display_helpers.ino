void drawScreen (int screen) {
  switch (screen) {
    case 0: //main screen
        //Draw clock:
        GLCD.SelectFont(Arial_bold_14); 
        GLCD.SetFontColor(BLACK);
        GLCD.CursorToXY(5,6);           
        if (hour < 10) {
          GLCD.print("0");
        }
        GLCD.print(hour); 
        GLCD.print(":");
        if (minute < 10) {
          GLCD.print("0");
        }
        GLCD.print(minute);
        GLCD.print("   "); //to clear if reducing signs 
        //Outdoor temp:
        GLCD.CursorToXY(90,6);
        GLCD.print(outdoorTemp,1);
        GLCD.SelectFont(System5x7);
        GLCD.print(char(128));
        GLCD.print(" "); //to clear if reducing signs 
        //Write status:
        GLCD.SelectFont(Callibri11);
        GLCD.CursorToXY(5,25);
        GLCD.print(systemStatus);
        GLCD.print("   "); //to clear if reducing signs 

        drawButtons("HEAT", "", "INFO");
        
      break;
    case 1: //sensor info screen
        //Write temp
        GLCD.SelectFont(System5x7);
        GLCD.CursorToXY(0,5);
        GLCD.print("  In: ");
        GLCD.print(indoorTemp,1);
        GLCD.print(char(128));
        GLCD.print(", ");
        GLCD.print(indoorHumidity,1);
        GLCD.println("% RH");
        GLCD.print(" Out: ");
        GLCD.print(outdoorTemp,1);
        GLCD.print(char(128));

        drawButtons(" HOME", "", "RELAYS");
      break;
  }

}


void drawButtons(char* str1, char* str2, char* str3) {
  GLCD.SelectFont(newbasic3x5);
  GLCD.SetFontColor(PIXEL_OFF);
  if (str1 != "") {
    GLCD.FillRoundRect(0, 55, 30, 8 ,3);  // rounded rectangle around text area   
    GLCD.DrawString(str1,3,55);
  }
  if (str2 != "") {
    GLCD.FillRoundRect(49, 55, 30, 8 ,3);  // rounded rectangle around text area   
    GLCD.DrawString(str2,53,55);
  }
  if (str3 != "") {
    GLCD.FillRoundRect(97, 55, 30, 8 ,3);  // rounded rectangle around text area   
    GLCD.DrawString(str3,101,55);
  }
  GLCD.SetFontColor(BLACK);
}
