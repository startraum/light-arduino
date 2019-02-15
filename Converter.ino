union ArrayToInteger {
  byte byte;
  uint32_t integer;
};


uint32_t toInt(byte b) {
  ArrayToInteger converter;
  converter.byte = b;
  return converter.integer;
}
