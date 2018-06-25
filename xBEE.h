/*
  xBEE.h - Library for cnfiguring and communicating with xBEE 802.15.4.
  Created by Kevin BEAUGRAND, June 16, 2018.
  Released into the public domain.
*/
#include <Arduino.h>

#ifndef xBEE_h
#define xBEE_h

class xBEE {
  public:
    /**
      Creates a new instance of the xBEE class.
    */
    xBEE();
    /**
      Creates a new instance of the xBEE class.
      @ni string reprensenting the Node Identifier.
    */
    xBEE(String ni);
    /**
      Creates a new instance of the xBEE class.
      @ni string reprensenting the Node Identifier.
      @ky string representing the AES Encryption Key.
    */
    xBEE(String ni, String ky);
    /**
      Configures the xBEE module to auto configure and auto-associate to a coordinator.
    */
    void AutoConfigure();
    /**
      Checks if the xBee is associated to a network.
      @returns True if associated, false otherwise.
    */
    bool IsAssociated();
    /**
      Starts the configuration of xBEE module.
      @returns True if configuration starts, false otherwise.
    */
    bool Configure();
    /**
      Writes the configuration to the xBEE module and finishes the configuration of xBEE module.
      @returns True if configuration ends, false otherwise.
    */
    bool Start();
    /**
      Sets the value of the xBEE register.
      @configuration the register name (e.g: DH, DL).
      @value the register value in hex.
      @returns True if configuration was set, false otherwise.
    */
    bool Set(String configuration, String value);
    /**
      Gets the value of the xBEE register.
      @configuration the register name (e.g: DH, DL).
      @returns The register value in hex.
    */
    String Get(String configuration);
    /**
      Sends a message to a remote device specified by DH, DL.
      @dl The Destination Low of the remote device.
      @dh The Destination High of the remote device.
      @content The message content
    */
    void Send(String dl, String dh, String content);
    /**
      Sends a message to a remote device specified by MY.
      @dl The MY of the remote device.
      @content The message content
    */
    void Send(String dl, String content);
    /**
      Sends a message the de configured destination device.
      @content The message content
    */
    void Send(String content);
    /**
      Checks if a message is availiable on the xBEE module.
      @retruns True if a message is availiable, False otherwise.
    */
    bool Available();
    /**
      Reads the availiable message.
      @retruns The message content for the xBEE module.
    */
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