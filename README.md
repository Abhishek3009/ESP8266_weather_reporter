# ESP8266_weather_reporter
IOT project using the NodeMCU esp8266 to gather weather data from https://openweathermap.org/ and displaying it on the OLED 128x64 display.

# NTP sever for date and time
To get time from an NTP Server, the ESP8266 needs to have an Internet connection and you don’t need additional hardware (like an RTC clock). NTP stands for Network Time Protocol and it is a networking protocol for clock synchronization between computer systems. There are NTP servers like pool.ntp.org that anyone can use to request time as a client. In this case, the ESP8266 is an NTP Client that requests time from an NTP Server (pool.ntp.org).

