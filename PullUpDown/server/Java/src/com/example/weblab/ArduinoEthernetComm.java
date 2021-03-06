package com.example.weblab;

import java.io.*;
import java.net.*;


public class ArduinoEthernetComm
{
	
	public String ArduinoEthernetComm(String serverIP, int serverPort, String msgToServer) throws Exception
	 {
					
		  String msgFromServer;//received message will be stored here  

		  Socket clientSocket = new Socket(serverIP, serverPort);//making the socket connection
		  System.out.println("Connected to:"+serverIP+" on port:"+serverPort);//debug
		  
		  //OutputStream to Arduino-Server
		  DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
		  
		  //BufferedReader from Arduino-Server
		  BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));//

		  //outToServer.writeBytes(msgToServer+'\n');//sending the message
		  outToServer.writeBytes(msgToServer);//sending the message
		  
		  System.out.println("sending to Arduino-Server: "+msgToServer);//debug
		  
		  //msgFromServer = inFromServer.readLine();
		  
	      //System.out.println("received from Arduino-Server: " + msgFromServer);//print the answer
		  clientSocket.close();
	      
		  return("OK");

	 }


}