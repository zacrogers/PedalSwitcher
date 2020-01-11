
#define BAUD_RATE 9600
bool serial_connected = false;

uint8_t ser_start_btn = 2;
uint8_t ser_stop_btn  = 3;

Gpio start_btn = Gpio(Port::D, 2, Mode::Input);
Gpio stop_btn  = Gpio(Port::D, 3, Mode::Input);

void setup(void)
{   
    pinMode(ser_start_btn, INPUT);
    pinMode(ser_stop_btn, INPUT);
    Serial.begin(BAUD_RATE);
}


void loop(void)
{
    if(digitalRead(ser_start_btn))
    {
        serial_connected = true;   
        Serial.begin(BAUD_RATE);
    }
    
    if(digitalRead(ser_stop_btn))
    {
        serial_connected = false; 
        Serial.end();
    }
    /*
    if(start_btn.read())
    {
        serial_connected = true;   
        Serial.begin(BAUD_RATE);
    }
    
    if(stop_btn.read())
    {
        serial_connected = false;   
        Serial.end();
    }    
    */
    
    if(serial_connected)
    {
        serial_loop();
    }
}

void serial_loop()
{
    if(Serial.available())
    {           
        serial_data = Serial.read();
        
        if(serial_data == "SYNC TO")
        {
            Serial.print("SYNCHED TO BOARD");
        } 
        
        if(serial_data == "SYNC FROM")
        {
            Serial.print("SYNCHED FROM BOARD");
        }
    }
}
