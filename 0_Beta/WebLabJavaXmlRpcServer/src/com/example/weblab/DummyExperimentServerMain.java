package com.example.weblab;

import es.deusto.weblab.experimentservers.IExperimentServer;
import es.deusto.weblab.experimentservers.Launcher;

public class DummyExperimentServerMain {
	public static void main(String [] args) throws Exception{
		IExperimentServer experimentServer = new DummyExperimentServer();
		Launcher launcher = new Launcher(40001, experimentServer);
		launcher.start();
	}
}
