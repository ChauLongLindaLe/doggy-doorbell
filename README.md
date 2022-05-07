# doggy-doorbell
An example to build a doggy doorbell using the Twilio ESP32 library

This is based off of the [Twilio ESP32 Library](https://github.com/ademuri/twilio-esp32-client),

## Build example:

In Arduino IDE, first ensure your ESP32 is burned with the Arduino bootloader and connected.  Then, merely adjust the globals in the secret.h and top of the .ino and hit the 'Upload' button.

You'll then want to edit the following variables in doggydoorbell.ino & secret.h:
* ssid: Your network SSID
* password: Network's password
* account_sid: from twilio.com/console
* auth_token: from twilio.com/console
* to_number: A number to send the SMS 
* from_number: An number from twilio.com/console authorized to send SMS
* message_body: Message body to send (Optional)
