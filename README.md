# AudioWayDSP
This repository is dedicated for the AudioWayDSP PCB Project. In this repository you are going to find the schematic of the board, a pcb Report document, a folder with the datasheets of the components i used with some notes i did that help me and were important for the development of the project and folder where i am going to upload custom firmware CubeIDE projects for the STM32 mcu.

# Circuit and PCB Design Summary
This audio development board is based to a STM32F302CBT6 that has 32KB of SRAM, 128KB of flash and it interfaces via I2S with TLV320AIC3254 audio codec that works in slave mode. Because I2S audio data quality depends upon quality clock signals, a 25MHZ external clock oscilator is important and it is used by the MCU as a referance clock in order to generate Master Clock, that the codec dedicated clock deviders devide it down to 48.000KHZ Sample frequency clock used by the adcs and dacs, but also the Audio data word and bit clocks. Because DAC/ADC and audio signal circuits in the codec are sensetive to noisy power rails i decided to use an AMS1117-3.3 LDO regulator with VCC input filtering and decoupling close to the IC power pins in order to limit the noise as much as possible.

As for the board IO, i have added a debug header that has SWD and UART pins for debuging, an I2C and a SPI header, 3 headers that connect with the MCU's ADCs, 3 stereo line inputs and one stereo line output that connect to the codec pins, a micro USB type B to power the board and interface with a computer via the MCU's USB FS but also a DC input header. Both the USB's DC input and DC input header have reverse polarity protection by using 2 Schottky Diodes that gives an option to use the usb and power the device using DC input header with different voltage.

# Basic Firmware Comfiguration
To initialize the system, HAL_I2C interface is used by the mcu to communicate with the codec and write specified values to specified configuration registers using the HAL_I2C_Mem_Write function to reset, enable and configure the codec system block. The codec datasheet provides basic initialization examples with the all important register addresses that you have to configure but also a Register Map with all the register addresses and their respective values.

# IS2 Data Streams
Once the codec is initialized, in order to do a simple test and see if everything works as intended i declared a int16[128] buffer array and used the HAL_I2S interface provided by STM. I iniatially configured i2s in I2S_MODE_MASTER_RX mode, sampling frequency  at I2S_AUDIOFREQ_48K, data format at I2S_DATAFORMAT_16B, clock polarity at I2S_CPOL_HIGH, and  i2s standard at I2S_STANDARD_PHILIPS and i called HAL_I2S_Receive function to see what data i was getting from the codec's adc. Although, the mcu was genarating all the clocks correctly and i was seeing data coming into the mcu using my oscilloscope, i was getting no data into the buffer. After 2 weeks of debugging and testing i finally found the cause of the problem with the help of the STM Community forum(Thread Link: https://community.st.com/s/question/0D53W00002CjuVsSAJ/hali2sreceive-gives-0s-although-codec-transmits-data). The problem was that these codecs in order to work in full duplex mode you have to do a full trasmit and receive circle so i had to configure i2s in I2S_MODE_MASTER_TX mode and use the HAL_I2SEx_TransmitReceive function also provided by STM32. After that i had data coming into the buffer but i had another issue. The data i was receiving were having the most segnificant bits 1 and the data where incorrert. That triggered my mind that the issue propably had to do with the i2s standard at I2S_STANDARD_PHILIPS and so i changed it to I2S_STANDARD_MSB because the datasheet also stated that most segnificants bits of the audio data are generated first and boom. The data i was getting were close 0 when input had no signal and signal and i had data when the input was a sine wave. So i passed the pointer of the receive funtion to the trasmit argument and the sine wave i was inputing was getting out from the codecs stereo output line. 

The audio output had that a little bit of a high noise floor and when the input was low i could hear it when i plugged the headphone but when i increased the volume noise was unnoticeable and the sound quality was good. I did some research on that too and it seems that i have to reconfigure some power options for best performance and enable some filtering blocks on the output in order to minimize the noise of the dac.

Lastly, i did some measurements at my uni's electronics lab where they have signal generators and higher bandwith digital osciloscopes so i could check the quality of the output signal. I tweaked the data format from I2S_DATAFORMAT_16B to I2S_DATAFORMAT_16B_Extended and changed the codecs data legnth setting register to 24bit as it seemed that i had better quality sinewave output. As of the frequency responce of the system in that simple configuration, i had flat response across the audio band(20-20khz).

# Firmware
In the firmware folder i have posted the CubeIDE project with the basic configuration but i am planning to populated it with more projects that implement digital audio processing algorithms in the future!

# Conclusion
This is my first mixed signal project where i designed and manufactured a more advanced 4-Layer pcb board which turned out pretty nice and i really enjoyed doing the research choosing components and reading the datasheets before doing the actual development and manufacturing of the board.
It was really fun and i am definatelly planning to do more projects like this in the future.

#Big Thanks to:
-- PhilsLab youtube channel which has a variety of content regarding these types of projects that i used as a reference and inspiration to build my own audio board
(https://www.youtube.com/@PhilsLab)

-- Netrona's Audio DSP project repository: https://github.com/Netrona/STM32F_Audio_Codec_pcb
-- har-in-air's repo that shares a stm32 i2s configuration that was helpful: https://github.com/har-in-air/STM32F411_USB_AUDIO_DAC
-- Hackaday stm32 microphone project: https://hackaday.io/project/181868-stm32f4-usb-microphone/details
-- Andybrown'sstm32 microphone project: https://andybrown.me.uk/2021/03/13/usb-microphone/
-- AIM65 Thread at diyAudio where he shared his digital preamp project featuring a I2S class d amp that interfaces with a STM32 mcu
(https://www.diyaudio.com/community/threads/neatamp-pre-a-digital-preamp-for-neatamp.373698/)
