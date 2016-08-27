void measurePower() {
  float sample = 0;
  
  relay(1,false); //turn off relay to measure zero point
  delay(100);
  for (int i = 0; i<1000; i++) {
    sample += analogRead(A2);
  }
  float zero = sample / 1000;
  Serial.print("1|");
  Serial.print(zero);
  
  relay(1,true); 
  delay(100);
  float sum;
  for (int i = 0; i<1000; i++) {
    sample = analogRead(A2) - zero;
    sum += sample * sample;
  }
  Serial.print("2|");
  Serial.print(sum);
  Serial.print("3|");  
  float rms = sum/1000;
  rms = sqrt(rms);
  Serial.print("4|");
  Serial.print(rms);
  rms = rms * 5;
  rms = rms / 1024;
  Serial.print("5|");
  Serial.println(rms);
  relay(1,false);
  delay(2000);  
}

