/*
  xBEEPractice.h - Library for cnfiguring and communicating with xBEE 802.15.4.
  Created by Kevin BEAUGRAND, June 16, 2018.
  Released into the public domain.
*/

#include "Arduino.h"

#ifndef xBEE_h
#define xBEE_h

class xBEE {
  public:
    xBEE();
    xBEE(String ni);
    xBEE(String ni, String ky);
    void AutoConfigure();
    bool IsAssociated();

    bool Configure();
    bool Start();
    bool Set(String configuration, String value);
    String Get(String configuration);

    void Send(String dl, String dh, String content);
    void Send(String dl, String content);
    
    bool Available();
    String Read();
  private:
    String _ni;
    String _ky;
    void startCommandMode();
    void endCommandMode();
    bool configureAndCheckResponse(String configuration, String value, String epectedResponse);
    String sendConfiguration(String configuration, String value);
};

#endif