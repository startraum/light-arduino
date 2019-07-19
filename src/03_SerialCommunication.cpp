bool SerialRead_Color() {
  byte color[5];
  Serial.readBytes(color, 5);
  r = color[0];
  g = color[1];
  b = color[2];
  w = color[3];
  animate=color[4];
  return false;
}

bool SerialWrite_actualState() {
  Serial.write(r);
  Serial.write(g);
  Serial.write(b);
  Serial.write(w);
  return false;
 }
