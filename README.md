### WeatherStation


A weather station can be described as an instrument or device, which provides us with the information of the weather parameters in the enclosed or ambient environment.Extraction of exact, accurate and real time weather data is essential in today’s scenario for various purposes, but existing methods of doing so are not efficient. This is owing to the large geographical distance between the weather station and the respective location of observation and even some human activities like industrialization affecting only a particular area.
Why exact data is required:
It is required for scientific and biological experimentation work-field. 
In the field of agriculture, accurate weather data of the ambient area of cultivation is essential for the growth certain crops.
Exact weather data is also required to aid home automation.
Pharmaceutical storage units and alike require specific parametric restriction like temperature and humidity.

For aiding these functionalities, a system is required which can log weather parameters accurately and efficiently. 

# Product Build

The main objective of the development of this IOT enabled Smart Weather Station is to make a weather monitor that wirelessly logs the temperature, dew point, humidity, pressure, and rain to a remote server so as to measure and access this data in real time and display it in a simple graphical user interface.With the help of these measurements, other weather parameters can be calculated such as the dew point, altitude, moisture level etc.

The brain of the prototype is the ESP8266 based Wi-fi module Node MCU (12E). Three sensors are connected to the Node MCU namely temperature and humidity sensor (DHT11), pressure sensor (BMP180), raindrop sensor with the help of jumper wires. This hardware component can be fit into a small box and placed anywhere as desired, hence making it handy and portable.

The data collected from the sensors are recorded in the AWS EC2 (ubuntu) cloud server database. The user can access and analyze the logged data from both web and mobile applications designed specifically for the prototype, using php and android. These GUIs are meant to easily analyze the changes in weather parameters of the ambience under observation.

# Product Scope

The product can find major use in the field of industry ,pharmaceutical and agriculture, as well as home/office automation .Because of it’s portability, it can be connected to a weather balloon and sent up to the different layers of the atmosphere to analyze the weather conditions in various regions in real-time. The periodic assessment of weather parameters can facilitate easy decisions dependent on them. It can also facilitate further automation of various devices like air conditioners, humidifier etc. It can be used to provide predictions based on collected data for optimized real-time solution.
This smart weather station finds its use in delivering statistical weather reports for prediction of oncoming storms or drastic depression to alert the municipality and government to prepare for the natural calamity and keep rescue operations ready in case of any emergency. It can be further modified by embedding MLX90614(cloud sensor) in the circuit to sense the cloud density present over the ambience to facilitate measurement of various other factors such as cloudy conditions, wind speed, wind direction, etc.



# Contributors

This product was developed by a group for college minor project. The contributors include:
-Veerangana Dash
-Mohit Sharma
-Utkarsh Jain
-Shrikriti Singh
