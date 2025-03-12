# Hovedprosjekt-V1

** You must use esp32 board library at version 2.0.11! Newer versions is not compatible! **

Encoder Library (Paul Stoffregen) for rotary encoders.
ezButtons for buttons.



## Module 1
Module 1 is the main module and includes:
- ESP 32
- Slider
- Potensiometer / Rotary Encoders
- USB C Connector ( 4 pin?)
- Magnets & Connectors on the left side only!
- Touch sensor on side to turn off?
- Compartments with sand (Weight)
- Magnets

## Module 2
Module 2 is an extension module and includes:
- 4-5 Buttons
- Oled
- Diffused leds on button press?
- Compartments with sand (Weight)
- Magnets & Connectors

## Module 3
Move stuff here??
- Magnets & Connectors
- Compartments with sand (Weight)


## Module 4
Module 4 is an external extra module that can work standalone aswell as connected. Use with Home Assistant
- 5 buttons
- Wemos D1 Mini
- USB C Connector
- Touch sensor??
- Compartments with sand (Weight)
- Magnets & Connectors

## Module 5
Module 5 is a dummy module designed to end off the Exodeck and hide the last connector. Evt sette connectors andre veien slik du ikkje får sideproblemet
- Magnets


## Connector pins:
1: 3.3v

2: 5v?

3: GND

4: SDA

5: SCL

6: Slider potensiometer Analog Read??

7: Button 1

8: Button 2

9: Button 3

10: Button 4

Note: Combine 2 and 2 buttons and use resistors and a analog read to save pins, if needed!


## General Keys

bleKeyboard.press(KEY_LEFT_CTRL);

bleKeyboard.press(KEY_LEFT_SHIFT);

bleKeyboard.press(KEY_LEFT_ALT);

bleKeyboard.press(KEY_LEFT_GUI);

bleKeyboard.press(KEY_RIGHT_CTRL);

bleKeyboard.press(KEY_RIGHT_SHIFT);

bleKeyboard.press(KEY_RIGHT_ALT);

bleKeyboard.press(KEY_RIGHT_GUI);

bleKeyboard.write(KEY_F1);

bleKeyboard.write(KEY_F2);

bleKeyboard.write(KEY_F3);

bleKeyboard.write(KEY_F4);

bleKeyboard.write(KEY_F5);

bleKeyboard.write(KEY_F6);

bleKeyboard.write(KEY_F7);

bleKeyboard.write(KEY_F8);

bleKeyboard.write(KEY_F9);

bleKeyboard.write(KEY_F10);

bleKeyboard.write(KEY_F11);

bleKeyboard.write(KEY_F12);

bleKeyboard.write(KEY_UP_ARROW);


## Media Keys

KEY_MEDIA_NEXT_TRACK

KEY_MEDIA_PREVIOUS_TRACK

KEY_MEDIA_STOP

KEY_MEDIA_PLAY_PAUSE

KEY_MEDIA_MUTE

KEY_MEDIA_VOLUME_UP

KEY_MEDIA_VOLUME_DOWN

KEY_MEDIA_WWW_HOME

KEY_MEDIA_LOCAL_MACHINE_BROWSER // Opens "My Computer" on Windows

KEY_MEDIA_CALCULATOR

KEY_MEDIA_WWW_BOOKMARKS

KEY_MEDIA_WWW_SEARCH

KEY_MEDIA_WWW_STOP

KEY_MEDIA_WWW_BACK

KEY_MEDIA_CONSUMER_CONTROL_CONFIGURATION // Media Selection

KEY_MEDIA_EMAIL_READER

bleKeyboard.write(KEY_DOWN_ARROW);

bleKeyboard.write(KEY_LEFT_ARROW);

bleKeyboard.write(KEY_RIGHT_ARROW);
