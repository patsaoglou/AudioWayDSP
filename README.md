# AudioWayDSP
This repository is dedicated for the AudioWayDSP PCB Project. In this repository you are going to find the schematic of the board, a pcb Report document, a folder with the datasheets of the components i used with some notes i did that help me and were important for the development of the project and folder where i am going to upload custom firmware CubeIDE projects for the STM32 mcu.

# Circuit and PCB Design Summary
This audio development board is based to a STM32F302CBT6 that has 32KB of SRAM, 128KB of flash and it interfaces via I2S with TLV320AIC3254 audio codec that works in slave mode. Because I2S audio data quality depends upon quality clock signals, a 25MHZ external clock oscilator is important and it is used by the MCU as a referance clock in order to generate Master Clock, that the codec dedicated clock deviders devide it down to 48.000KHZ Sample frequency clock used by the adcs and dacs, but also the Audio data word and bit clocks. Because DAC/ADC and audio signal circuits in the codec are sensetive to noisy power rails i decided to use an AMS1117-3.3 LDO regulator with VCC input filtering and decoupling close to the IC power pins in order to limit the noise as much as possible.

As for the board IO, i have added a debug header that has SWD and UART pins for debuging, an I2C and a SPI header, 3 headers that connect with the MCU's ADCs, 3 stereo line inputs and one stereo line output that connect to the codec pins, a micro USB type B to power the board and interface with a computer via the MCU's USB FS but also a DC input header. Both the USB's DC input and DC input header have reverse polarity protection by using 2 Schottky Diodes that gives an option to use the usb and power the device using DC input header with different voltage.

# Basic Firmware Comfiguration
To initialize the system, HAL_I2C interface is used by the mcu to communicate with the codec and write specified values to specified configuration registers using the HAL_I2C_Mem_Write function to reset, enable and configure the codec system block. The codec datasheet provides basic initialization examples with the all important register addresses that you have to configure but also a Register Map with all the register addresses and their respective values.

# IS2 Data Streams
Once the codec is initialized, in order to do a simple test and see if everything i declared a int16[128] buffer array and used the HAL_I2S interface provided by STM. I iniatially configured i2s in I2S_MODE_MASTER_RX mode, sampling frequency  at I2S_AUDIOFREQ_48K, data format at I2S_DATAFORMAT_16B, clock polarity at I2S_CPOL_HIGH, and  i2s standard at I2S_STANDARD_PHILIPS and i called HAL_I2S_Receive function to see what data i was getting from the codec's adc. Although, the mcu was genarating all the clocks correctly and i was seeing data coming into the mcu using my osciloscope, i was getting no data into the buffer. After 2 weeks of debugging and testing i finally found the cause of the problem with the help of the STM Community forum(Thread Link: ).
