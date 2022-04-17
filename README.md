LibAVRpp
========

A high-level but efficient C++20 library for your AVR project.

# EEPROM\_var

Accessing variables stored in the EEPROM as they were normal variables. Also support for arrays.

## Example
Array of function pointers
```C++
#include<eeprom_var.hpp>

const avr::eeprom_array animations [[gnu::section(".eeprom")]] = {fade, onoff<1000>, onoff<500>, rotate<1000>};

void function(){
	const decltype(teszt)::value_type act_anim = teszt[anim_index];
	act_anim();
}
```
Simple integer in EEPROM (it is accessed through a *'reference'*)
```C++
#include<eeprom_var.hpp>

const uint16_t example [[gnu::section(".eeprom")]] = 7;

void function(){
	avr::eeprom_ref example_ref {&example};
	uint16_t a = 5 + example_ref;
}
```

