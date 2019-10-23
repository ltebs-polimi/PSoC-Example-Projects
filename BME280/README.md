# BME280 Project

This project allows to implement a communication between a PSoC 5LP (using a [CY8CKIT-059](https://www.cypress.com/documentation/development-kitsboards/cy8ckit-059-psoc-5lp-prototyping-kit-onboard-programmer-and) development kit) and a [BME280 sensor](https://www.bosch-sensortec.com/bst/products/all_products/bme280).

## BME280 Sensor
The BME280 is an integrated environmental sensor developed specifically for mobile applications where size and low power consumption are key design constraints. The unit combines individual high linearity, high accuracy sensors for pressure, humidity and temperature in an 8-pin metal-lid LGA package.

## Projects
The project was developed using PSoC Creator. The workspace that you can find in this repository contains the following PSoC Creator projects:
 - 01-BME280: this is the basic project that you can use as start project. It contains the I2C interface for communication, and the BME280 library. 