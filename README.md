# My home automation display

## Introduction
This projects shows the status of my HomeAssistant system on a [Waveshare 7" LCD](https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-7) display.

## Set-Up

## Pages

### Car

### Debug

### Internet

### Messages

### NAS

### Printer

### Solar

### Time

### Weather

## Additional functions

### background image

### motion sensor

### deep sleep

### fonts

**common/const.yaml:** This file contains definitions for the characters onf the [Material Design Icons](https://pictogrammers.com/library/mdi/) font. With these definitions is is possible to write eg. $mdi_compass instead of \U000F018B.
It is using a copy of the materialdesignicons-webfont.ttf font downloaded from [GitHub](https://github.com/Templarian/MaterialDesign-Webfont/tree/master). The font is licensed under the [Apache 2.0 license](https://www.apache.org/licenses/LICENSE-2.0) and copyrighted by [Pictogrammers](https://pictogrammers.com/). Fot texts, the Google-Font Montserrat is used. It is licensed under [SIL Open Font License, Version 1.1](https://openfontlicense.org/open-font-license-official-text/) and copyrighted by the [Montserrat Git Project Authors](https://github.com/JulietaUla/Montserrat.git).

**lcd/fonts.yaml:** Here are the font definitions. The following fonts are used in this project:
* _font_time:_ A big font used to show the clock on the top-right of the screen. This font just consists of digits an a colon.
* _font_mid:_ The default font in this project. It is a 25 point font with the normal characters, German umlauts and many idons from the Material Design Icons font.
* _font_small:_ A small font to show short texts eg. for the weather forecast.
* _font_footer:_ 15pt font used in the footer only.