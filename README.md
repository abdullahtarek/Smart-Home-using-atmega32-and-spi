# Smart-Home-using-atmega32-and-spi

This project is aimed to put most of the embedded concepts in one project. It contains EEPROM,interrupts, timers, SPI , LCD , keypad and ADC with a temperature sensor. All integrated in one project using free RTOS operaing systems.
First the user is given a login page to choose whether he is a guest or an admin. The admin has full control the lights in the Rooms and TV and AC, but the guest only has control ver the rooms. when the Admin logs in for the first time the user is required to set a password that password is saved in the EEPROM so that next time the user puts the passwords and it is compared with the stored password. Then after loging in if the user wants to switch on or off any device the user just enters a number from one to five that is displayed on the lcd screen. When the user sets the AC on the program sees the temprature sensor if the tempretature is less than the required tempreture plus the AC will not open if it is moe the AC will open. maing the room the desired tempreture



<img src="https://github.com/abdullahtarek/Smart-Home-using-atmega32-and-spi/blob/master/Screenshot_1.png" />
</br>
