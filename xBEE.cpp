#include <Arduino.h>
#include <xBEE.h>

xBEE::xBEE()
{
  _ni = "";
  _ky = "0";
}

xBEE::xBEE(String ni)
{
  _ni = ni;
  _ky = "";
}

xBEE::xBEE(String ni, String ky)
{
  _ni = ni;
  _ky = ky;
}

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

bool xBEE::IsAssociated(){
  return configureAndCheckResponse("AI", "", "0");
}

bool xBEE::Configure()
{
  startCommandMode();
}

bool xBEE::Start()
{
  endCommandMode();
}

bool xBEE::Set(String configuration, String value)
{
  configureAndCheckResponse(configuration, value, "OK");
}

String xBEE::Get(String configuration)
{
  sendConfiguration(configuration, "");
}

void xBEE::Send(String dl, String dh, String content)
{
  startCommandMode();
  configureAndCheckResponse("DL", dl, "OK");
  configureAndCheckResponse("DH", dh, "OK");
  endCommandMode();
  
  Serial.println(content);
}

void xBEE::Send(String dl, String content)
{    
  startCommandMode();
  configureAndCheckResponse("DL", dl, "OK");
  configureAndCheckResponse("DH", "0", "OK");
  endCommandMode();
  
  Serial.println(content);
}

bool xBEE::Available()
{
  return Serial.available();
}

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
