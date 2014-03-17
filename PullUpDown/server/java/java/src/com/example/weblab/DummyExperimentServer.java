package com.example.weblab;

import java.io.File;

import javax.sound.sampled.LineUnavailableException;


import es.deusto.weblab.experimentservers.ExperimentServer;
import es.deusto.weblab.experimentservers.exceptions.ExperimentServerInstantiationException;
import es.deusto.weblab.experimentservers.exceptions.WebLabException;

public class DummyExperimentServer extends ExperimentServer {

	public DummyExperimentServer()
			throws ExperimentServerInstantiationException {
		super();
	}

	public void startExperiment() throws WebLabException {
		System.out.println("I'm at startExperiment");
	}

	public String sendFile(File file, String fileInfo)  throws WebLabException {
		System.out.println("I'm at send_program: " + file.getAbsolutePath() + "; fileInfo: " + fileInfo);
		return "ok";
	}
	
	public String sendCommand(String command)  throws WebLabException {
		
		/*
		String comando = String.valueOf(command.charAt(command.length()-1));
			
			ArduinoEthernetComm aec = new ArduinoEthernetComm();
			
			try {
				//Colocar estes dados retornados no documento csv ou retornar ao usuário para exibir o gráfico
				System.out.println("Dados Arduino => " + aec.ArduinoEthernetComm("192.168.42.2",80,comando));
				
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			
			
			}
			
			*/
			
			return "visualize o resultado...";
		
	}
	
	public void dispose() {
		System.out.println("I'm at dispose");
		

		
	}
	
	/* Optional methods (Override, Java 1.4 compatible...) */
	
	public boolean isUpAndRunning() {
		return false;
	}
}
