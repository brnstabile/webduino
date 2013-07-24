// NAME
//      $RCSfile: BeanCanApplet.java,v $
// DESCRIPTION
//      [given below in javadoc format]
// DELTA
//      $Revision$
// CREATED
//      $Date$
// COPYRIGHT
//      Mexuar Technologies Ltd
// TO DO
//
package org.asteriskjava.iax.ui;

import java.awt.*;
import java.applet.*;
import org.asteriskjava.iax.audio.javasound.AudioProperties;
import org.asteriskjava.iax.protocol.Call;
import org.asteriskjava.iax.protocol.Friend;
import org.omg.CORBA._PolicyStub;

/**
 * Swing phone implementation
 * @author <a href="mailto:thp@westhawk.co.uk">Tim Panton</a>
 * @version $Revision$ $Date$
 *
 */
public class BeanCanApplet
    extends Applet {
    private static final String version_id =
        "@(#)$Id$ Copyright Mexuar Technologies Ltd";

  private boolean isStandalone = false;
  String host = null;
  String user = null;
  String pass = null;
  Integer debug;
  BeanCanFrameManager bcf;
  private String audioIn;
  private String audioOut;

  //Get a parameter value
  public String getParameter(Object target, String key, String def) {
    String ret;
    if (target == null) {
      ret = getParameter(key, def);
    }
    else {
      ret = target.toString();
    }
    return ret;
  }

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
        (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public BeanCanApplet() {

  }

  //Initialize the applet
  public void init() {
    try {
      host = this.getParameter(host, "host", "IP_ADDRESS_SERVER");
    }
    catch (Exception e) {
      e.printStackTrace();
    }
    try {
      user = this.getParameter(user, "user", "REGISTERED_USER");
    }
    catch (Exception e) {
      e.printStackTrace();
    }
    try {
      pass = this.getParameter(pass, "pass", "PASSWORD_FOR_USER");
    }
    catch (Exception e) {
      e.printStackTrace();
    }
    try {
      debug = new Integer(this.getParameter(debug, "debug", "0"));
    }
    catch (Exception e) {
      e.printStackTrace();
    }
    try {
      audioIn = this.getParameter(audioIn, "AudioInputDevice", null);
      if (null != audioIn) {
        AudioProperties.setInputDeviceName(audioIn);
      }
    }
    catch (Exception e) {
      e.printStackTrace();
    }
    try {
      audioOut = this.getParameter(audioOut, "AudioOutputDevice", null);
      if (null != audioOut){
        AudioProperties.setOutputDeviceName(audioOut);
      }
    }
    catch (Exception e) {
      e.printStackTrace();
    }

    try {
      jbInit();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }

  //Component initialization
  private void jbInit() throws Exception {
    bcf = new BeanCanFrameManager(true, debug.intValue(), host);
    bcf.validate();

  }

  //Start the applet
  public void start() {
    if (bcf.canRecord()) {
      restart();
    }
    else {
      CantRecordDialog crd = new CantRecordDialog(this, bcf,
                                                  "No permission to access microphone", false);
      crd.show();
    }
  }

  void restart() {
    if (bcf != null) {
      bcf.set_host(host);
      bcf.set_username(user);
      bcf.set_password(pass);
      bcf.set_debug(debug.intValue());
      bcf.start();
      bcf.register();

    }
  }

  //Stop the applet
  public void stop() {
    if (bcf != null) {
      bcf.stop();
    }
  }

  //Destroy the applet
  public void destroy() {
  }

  //Get Applet information
  public String getAppletInfo() {
    return "Westhawk's IJAX 2 softphone www.westhawk.co.uk";
  }

  //Get parameter info
  public String[][] getParameterInfo() {
    String[][] pinfo = {
        {
        "host", "String", ""}
        , {
        "user", "String", ""}
        , {
        "pass", "String", ""}
        , {
        "debug", "int", ""}
        , {
        "audioIn", "String", ""}
        , {
        "audioOut", "String", ""}
    };
    return pinfo;
  }
}
