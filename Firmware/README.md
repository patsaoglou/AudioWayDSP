Directory for firmware source files made with STMCubeIDE

AudioWayDSP - 1: 
  Basic firmware for the TLV320AIC3254 codec: 
  1. Connecting left and right IN1-L IN1-R to left and right adc
  2. Powering up analog blocks, adc's and dac.
  3. Connecting left and right dac with LOL LOR
  4. Calling HAL_I2SEx_TransmitReceive to start the input/output audio data streams
  5.  Sampling Frequency: 48.000khz
      Data size: 16Bit Extended
  Note: Check in main.c file the function void tlv320_Init(I2C_HandleTypeDef *hi2c2).
