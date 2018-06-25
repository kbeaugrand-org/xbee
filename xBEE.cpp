#include <Arduino.h>
#include <xBEE.h>

/**
  Creates a new instance of the xBEE class.
*/
xBEE::xBEE()
{
  _ni = "";
  _ky = "0";
}

/**
  Creates a new instance of the xBEE class.
  @ni string reprensenting the Node Identifier.
*/
xBEE::xBEE(String ni)
{
  _ni = ni;
  _ky = "";
}

/**
  Creates a new instance of the xBEE class.
  @ni string reprensenting the Node Identifier.
  @ky string representing the AES Encryption Key.
*/
xBEE::xBEE(String ni, String ky)
{
  _ni = ni;
  _ky = ky;
}

/**
  Configures the xBEE module to auto configure and auto-associate to a coordinator.
*/
void xBEE::AutoConfigure()
{
  startCommandMode();

  String ee;

  if ( _ky.length() == 0 )
  {
    ee = "0";    
  }
  else
  {
     ee = "1";
  }

  if (!(configureAndCheckResponse("RE", "", "OK") && 
    configureAndCheckResponse("NI", _ni, "OK") &&
    configureAndCheckResponse("EE", ee , "OK") &&
    configureAndCheckResponse("KY", _ky , "OK") &&
    configureAndCheckResponse("A1", "7", "OK") &&
    configureAndCheckResponse("NO", "1", "OK") &&
    configureAndCheckResponse("WR", "", "OK")))
    {
      return false;
    }

   while(!IsAssociated())
   {
      delay(500);
   }
   
   endCommandMode();
}

/**
  Checks if the xBee is associated to a network.
  @returns True if associated, false otherwise.
*/
bool xBEE::IsAssociated(){
  return configureAndCheckResponse("AI", "", "0");
}

/**
  Starts the configuration of xBEE module.
  @returns True if configuration starts, false otherwise.
*/
bool xBEE::Configure()
{
  startCommandMode();
}

/**
  Writes the configuration to the xBEE module and finishes the configuration of xBEE module.
  @returns True if configuration ends, false otherwise.
*/
bool xBEE::Start()
{
  endCommandMode();
}
/**
  Sets the value of the xBEE register.
  @configuration the register name (e.g: DH, DL).
  @value the register value in hex.
  @returns True if configuration was set, false otherwise.
*/
bool xBEE::Set(String configuration, String value)
{
  configureAndCheckResponse(configuration, value, "OK");
}
/**
  Gets the value of the xBEE register.
  @configuration the register name (e.g: DH, DL).
  @returns The register value in hex.
*/
String xBEE::Get(String configuration)
{
  sendConfiguration(configuration, "");
}
/**
  Sends a message to a remote device specified by DH, DL.
  @dl The Destination Low of the remote device.
  @dh The Destination High of the remote device.
  @content The message content
*/
void xBEE::Send(String dl, String dh, String content)
{
  startCommandMode();
  configureAndCheckResponse("DL", dl, "OK");
  configureAndCheckResponse("DH", dh, "OK");
  endCommandMode();
  
  Serial.println(content);
}
/**
  Sends a message to a remote device specified by MY.
  @dl The MY of the remote device.
  @content The message content
*/
void xBEE::Send(String dl, String content)
{    
  startCommandMode();
  configureAndCheckResponse("DL", dl, "OK");
  configureAndCheckResponse("DH", "0", "OK");
  endCommandMode();
  
  Serial.println(content);
}
/**
  Sends a message.
  @content The message content
*/
void xBEE::Send(String content)
{    
  Serial.println(content);
}
/**
  Checks if a message is availiable on the xBEE module.
  @retruns True if a message is availiable, False otherwise.
*/
bool xBEE::Available()
{
  return Serial.available();
}
/**
  Reads
  @retruns The message content for the xBEE module.
*/
String xBEE::Read()
{
  if(!Available())
  {
    return "";
  }
  
  return Serial.readString();
}


void xBEE::startCommandMode(){
  Serial.print("+++");
  
  for(int i =0; i< 3; i++){
      delay(1000);
  }
}

void xBEE::endCommandMode(){
  configureAndCheckResponse("WR", "", "OK") &&
  configureAndCheckResponse("CN", "", "OK");
}

String xBEE::sendConfiguration(String configuration, String value) {
  Serial.println("AT" + configuration + " " + value);
  
  while (!Serial.available()) { }

  return Serial.readString();
}

bool xBEE::configureAndCheckResponse(String configuration, String value, String expectedResponse) {
  String response = sendConfiguration(configuration, value);

  if (response.indexOf(expectedResponse) >= 0) {
    return true;
  }
  else {    
    return false;
  }
}
