[Back to main page](PetFeeder.md)

## Solar Panel ##
The whole device works autonomously, without any external AC/DC power supply. For powering I use a 1.5 watt/12 volt solar panel.
There are many of them at ebay for about 10$.
![http://1.bp.blogspot.com/-m06h4Ey1Zcc/TvnbjGoddZI/AAAAAAAAAUc/sU_fTY3dyEw/s1600/solar_panel.jpg](http://1.bp.blogspot.com/-m06h4Ey1Zcc/TvnbjGoddZI/AAAAAAAAAUc/sU_fTY3dyEw/s1600/solar_panel.jpg)
I mounted a panel outdoor at safe place to prevent it from bad weather conditions and same time let to get more solar light. The panel gives enough power even in very cloudy weather. Keep in mind that window glass isn't 100% transparent.

## Rechargeable Battery ##
The device should work all the time, even in bad weather or dark time, therefore I need some battery to supply it at that time when there is no sufficient solar power. I used very simple 6Volt VRLA battery with capacity 4AH. Even if we suppose that this battery really gives out only 1AH, it will be enough to power the device few days without solar energy (device average consumption is 1.5-2ma).
![http://2.bp.blogspot.com/-pd0YxraAKtI/TvnbhF4i_LI/AAAAAAAAAUE/YHRITuZDd6s/s1600/Battery.jpg](http://2.bp.blogspot.com/-pd0YxraAKtI/TvnbhF4i_LI/AAAAAAAAAUE/YHRITuZDd6s/s1600/Battery.jpg)
The battery is charging via solar panel. Atmega controls charging process via electrical scheme.
Charging algorithm is very simple, goal is floating voltage for VRLA battery that is mentioned in datasheet. If voltage from solar panel is greater then battery voltage and battery voltage is less then floating voltage, then the MOSFET opens and charging starts.
Here is a part of code