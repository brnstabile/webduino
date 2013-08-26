package org.asteriskjava.iax.ui;

import org.asteriskjava.iax.audio.javasound.AudioProperties;
import org.asteriskjava.iax.protocol.Call;
import org.asteriskjava.iax.protocol.Friend;
import org.asteriskjava.iax.protocol.Log;
import org.asteriskjava.iax.protocol.ProtocolControlFrame;

public class main {
	
	static final String _host = "192.168.30.177" ;
	static final String _username = "1003" ;
	static final String _password = "12345" ;
	static final String _exp = "1004" ;
	
	/**
	 * @param args
	 */
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		 
	    AudioProperties.loadFromFile("audio.properties");
		
		BeanCanFrameManager frameManager = new BeanCanFrameManager(false,Log.DEBUG,"");
	
		if(frameManager != null){
			
			frameManager.set_host(_host);
			frameManager.set_username(_username);
			frameManager.set_password(_password);
			frameManager.register();
			frameManager.dialString.setText(_exp);
			frameManager.act.doClick();

		}

	}

}
