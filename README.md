## Aninipot Neopixels Library Version
a light exploration using Neopixels LEDs used as a notifier for incoming *dropcalls* for GhostWhisper modules.

## Installation Instructions:

    Edit Data Pin and LED Count at "LightingModes.cpp" if you are using different pins and/or number of LEDs.

    Clone the repository from **https://github.com/Internet-Pavilion-PH/aninipot/tree/neopixels-version** and open it in PlatformIO by clicking the PlatformIO icon on the left panel. Under "Quick Access" open "PIO Home" and click "Open", this will lead you to the PlatformIO homepage. Click "Import Arduino Project" and select "NodeMCU-32S" as your board. Click on the directory that contains the ghostwhisper folder downloaded from the github link above. Open the ghostwhisper folder and click IMPORT.

    On the second to the left panel of your workspace, under "ANINIPOT", open the "src" folder and open "main.cpp".

    Connect the ESP32 to your computer using the data cable (USB-C to USB-A) it came with and click the upload button in PlatformIO. Make sure to press the BOOT button of the ESP32 while uploading the code, do not release the button until the code has been fully uploaded. Once the upload is done, press the RTS (reset) button of the ESP32 to refresh the program on the ESP32.

    Keep the ESP32 plugged into your computer for the next step.


## After installation, configure the ESP32 to access the WiFi. You may use your computer or phone for this step.

   Open your WiFi Settings and connect to the SSID name **aninipot**, this will redirect you to the **WiFiManager** landing page of ghostwhisper.

   Click on the **Configure WiFi** button and enter the WiFi credentials (SSID and Password). Once done this will save the WiFi credentials and connect the ESP32 to the network.

   Once connected to the WiFi, you will hear a sound indicating that the connection was successful. If the sound doesn't play, there might be a problem with the credentials entered–– troubleshoot this by reconfiguring the WiFi Settings.

   Unplug the ESP32 from your computer once the connection is successful.


## Artwork Operation

   Connect the USB-C end of the Power Supply Unit to the ESP32 microcontroller.

   Plug the Power Supply Unit into an outlet. The work will automatically boot in a few seconds.

   Access the app through kolown.net/dropcall to create a recording. Tap the record button, record your message, and tap send.

   Wait for the Aninipot's lights to blink in real time; GhostWhisper will play the sound shortly thereafter.

   To turn the piece ON or OFF, plug or unplug the Power Supply Unit from the outlet. Alternatively, the Power Supply Unit may be plugged into an adaptor with a switch or a powerstrip that has a switch.