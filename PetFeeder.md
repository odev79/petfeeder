# Introduction #

The project goal is to feed pets (cats, dogs, etc...) automatically, controlled by programmable schedule and operating autonomously without any maintenance (except adding food in device) and without any external AC or DC power.

The device is powered by solar panel and rechargeable battery that guarantees 5-6 days power without solar energy (in case of very bad weather).

The battery charging and feeding schedule is controlled via Atmega328 (Arduino MiniPro) and custom designed electrical circuit.

# Details #

The project consists of hardware ([the device](PetFeeder#The_Device.md)) and software ([Arduino code](http://code.google.com/p/petfeeder/source/browse/#svn%2Ftrunk)) parts.

## The Device ##
Device itself consists of
  * [Food Container](mechanics#Food_Container.md)
  * [Food Feeding Part](mechanics#Food_Feeding_Part.md)
  * [Solar Panel](Power#Solar_Panel.md)
  * [VRLA Rechargeable Battery](Power#Rechargeable_Battery.md)
  * Microcontroller and Electrical Circuit to control whole hardware