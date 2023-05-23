# AudioWayDSP
This repository is dedicated for the AudioWayDSP PCB Project. In this repository you are going to find the schematic of the board, a pcb Report document, a folder with the datasheets of the components i used with some notes i did that help me and were important for the development of the project and a folder where i am going to upload custom firmware CubeIDE projects for the STM32 mcu. I made this audio development board because i wanted to interface my audio projects like headphone/audio amplifiers and mic amplifiers with the digital domain.

![20230408_124634](https://user-images.githubusercontent.com/93339707/230942115-1fff1c84-43ac-4412-8835-438c6a74595b.jpg)

# Circuit and PCB Design Summary
This audio development board is based to a STM32F302CBT6 that has 32KB of SRAM, 128KB of flash and it interfaces via I2S with the TLV320AIC3254 audio codec that works in slave mode. Because I2S audio data quality depends upon quality clock signals, a 25MHZ external clock oscillator is important and it is used by the MCU as a reference clock in order to generate Master Clock, that the codec's dedicated clock deviders devide it down to 48.000KHZ Sample frequency clock used by the adcs and dacs, but also the Audio data word and bit clocks. Because DAC/ADC and the audio signal circuits in the codec are sensetive to noisy power rails i decided to use an AMS1117-3.3 LDO regulator with VCC input filtering and decoupling close to the IC power pins in order to limit the noise as much as possible.

![20230408_124800](https://user-images.githubusercontent.com/93339707/230942482-17a5ab97-9a17-4d35-8651-e696cb9beba7.jpg)

As for the board IO, i have added a debug header that has SWD and UART pins for debuging, an I2C and a SPI header, 3 headers that connect with the MCU's ADCs, 3 stereo line inputs and one stereo line output that connect to the codec pins, a micro USB type B to power the board and interface with a computer via the MCU's USB FS but also a DC input header. Both the USB's DC input and DC input header have reverse polarity protection by using 2 Schottky Diodes that gives an option to use the usb and power the device using the DC input header with different voltage.

![20230408_123720](https://user-images.githubusercontent.com/93339707/230942542-c760dc08-2def-4060-b035-fbc0476e106d.jpg)

# Basic Firmware Configuration
To initialize the system, HAL_I2C interface is used by the mcu to communicate with the codec and write specified values to specified configuration registers using the HAL_I2C_Mem_Write function to reset, enable and configure the codec's system blocks. The codec's datasheet provides basic initialization examples with the all important register addresses that you have to configure but also a Register Map with all the register addresses and their respective values.

# IS2 Data Streams
Once the codec is initialized, in order to do a simple test and see if everything works as intended i declared a int16[128] buffer array and used the HAL_I2S interface provided by STM. I initially configured i2s in I2S_MODE_MASTER_RX mode, sampling frequency  at I2S_AUDIOFREQ_48K, data format at I2S_DATAFORMAT_16B, clock polarity at I2S_CPOL_HIGH, i2s standard at I2S_STANDARD_PHILIPS and i called HAL_I2S_Receive function to see what data i was getting from the codec's adc. Although, the mcu was genarating all the clocks correctly and i was seeing data coming into the mcu using my oscilloscope, i was getting no data into the buffer. After 2 weeks of debugging and testing i finally found the cause of the problem with the help of the STM Community forum(Thread Link: https://community.st.com/s/question/0D53W00002CjuVsSAJ/hali2sreceive-gives-0s-although-codec-transmits-data). The problem was that these codecs in order to work in full duplex mode you have to do a full trasmit and receive circle so i had to configure i2s in I2S_MODE_MASTER_TX mode and use the HAL_I2SEx_TransmitReceive function also provided by STM32. After that i had data coming into the buffer but i had another issue. The data i was receiving were having the most segnificant bits 1 and the data were incorrert. That triggered my mind that the issue propably had to do with the i2s standard at I2S_STANDARD_PHILIPS and so i changed it to I2S_STANDARD_MSB because the datasheet also states that most segnificant bits of the audio data are generated first. The data i was getting were close 0 when the input had no signal and i had data when the input was a sine wave. So i passed the pointer of the receive function to the trasmit argument and the sine wave i was inputing, was getting out from the codecs stereo output line. 

![20230401_033923](https://user-images.githubusercontent.com/93339707/230942313-cda9be3b-ccf2-4e36-a6f2-c3fe1a216384.jpg)

The audio output had a little bit of a high noise floor and when the input was low i could hear it when i plugged the headphones, but when i increased the volume, noise was unnoticeable and the sound quality was good. I did some research on that too and it seems that i have to reconfigure some power options for best performance and enable some filtering blocks on the output in order to minimize the noise of the dac.

![20230408_124101](https://user-images.githubusercontent.com/93339707/230942370-556aad7b-2244-40bd-bb3a-6abcd4377a5a.jpg)

Additionally, i did some measurements at my uni's electronics lab where they have signal generators and higher bandwith digital osciloscopes so i could check the quality of the output signal. I tweaked the data format from I2S_DATAFORMAT_16B to I2S_DATAFORMAT_16B_Extended and changed the codecs data length register to 24bit as it seemed that i had better quality sinewave output. As of the frequency responce of the system in that simple configuration, i had flat response across the audio band(20-20khz).

Finally, i did some last measurements with a low-pass filter with a cutoff frequency @33khz to limit the noise coming from the dac output of the codec and i have a nice and clean audio signal with less than 5mv of noise!
![346106683_938365657493886_9105701429267784199_n](https://github.com/patsaoglou/AudioWayDSP/assets/93339707/6a3378d7-7310-44b6-b46f-10d96741ac2b)

# Firmware
In the firmware folder i have posted the CubeIDE project with the basic configuration but i am planning to populated it with more projects that implement digital audio processing algorithms in the future!

# Big Thanks to:

-- PhilsLab youtube channel which has a variety of content regarding these types of projects that i used as a reference and inspiration to build my own audio board
(https://www.youtube.com/@PhilsLab)

-- Netrona's Audio DSP project repository: https://github.com/Netrona/STM32F_Audio_Codec_pcb

-- har-in-air's repo that shares a stm32 i2s configuration that was helpful: https://github.com/har-in-air/STM32F411_USB_AUDIO_DAC

-- Hackaday stm32 microphone project: https://hackaday.io/project/181868-stm32f4-usb-microphone/details

-- Andybrown's stm32 microphone project: https://andybrown.me.uk/2021/03/13/usb-microphone/

-- AIM65 Thread at diyAudio where he shared his digital preamp project featuring a I2S class d amp that interfaces with a STM32 mcu
(https://www.diyaudio.com/community/threads/neatamp-pre-a-digital-preamp-for-neatamp.373698/)

# Conclusion
This is my first mixed signal project where i designed and manufactured a more advanced 4-Layer pcb board which turned out pretty nice and i really enjoyed doing the research choosing components and reading the datasheets before doing the actual development and manufacturing of the board.
It was really fun and i am definatelly planning to do more projects like this in the future.

# Pinout
--MCU Pinout

![MCU PINOUT](https://user-images.githubusercontent.com/93339707/230944513-bfe624c0-bfe5-44ff-8c89-22491e554c47.PNG)

--Debug header Pinout

![DEBUG header](https://user-images.githubusercontent.com/93339707/230945974-e8dcfcb8-5ed8-495e-92a9-f326ddc6ac51.PNG)

--3 Line in headers

![line in](https://user-images.githubusercontent.com/93339707/230945746-c7af9072-e3cb-43c2-8e83-2a5a8cb9e061.PNG)

--Line out, I2C and spi header

![LINE OUT  I2C, SPI HEADER](https://user-images.githubusercontent.com/93339707/230945920-65fcbfe2-8aab-4b61-b26a-9ff0fc354be4.PNG)

--One of the 3 adc headers

![adc](https://user-images.githubusercontent.com/93339707/230946078-22a31f2c-8d24-4fea-8bc6-e8daab094685.PNG)
