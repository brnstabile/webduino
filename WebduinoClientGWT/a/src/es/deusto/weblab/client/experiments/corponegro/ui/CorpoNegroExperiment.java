/*
* Copyright (C) 2012 onwards University of Deusto
* All rights reserved.
*
* This software is licensed as described in the file COPYING, which
* you should have received as part of this distribution.
*
* This software consists of contributions made by many individuals, 
* listed below:
*
* Author: FILLME
*
*/

package es.deusto.weblab.client.experiments.corponegro.ui;

import com.google.gwt.core.client.GWT;
import com.google.gwt.json.client.JSONObject;
import com.google.gwt.json.client.JSONParser;
import com.google.gwt.json.client.JSONValue;
import com.google.gwt.user.client.ui.VerticalPanel;

import es.deusto.weblab.client.comm.exceptions.CommException;
import es.deusto.weblab.client.configuration.IConfigurationRetriever;
import es.deusto.weblab.client.ui.widgets.IWlActionListener;
import es.deusto.weblab.client.lab.experiments.IBoardBaseController;
import es.deusto.weblab.client.lab.experiments.UIExperimentBase;
import es.deusto.weblab.client.ui.widgets.IWlWidget;
import es.deusto.weblab.client.ui.widgets.WlButton;
import es.deusto.weblab.client.ui.widgets.WlStreamImage;
import es.deusto.weblab.client.ui.widgets.WlSwitch;
import es.deusto.weblab.client.ui.widgets.WlTimer;
import es.deusto.weblab.client.ui.widgets.WlWebcam;

public class CorpoNegroExperiment extends UIExperimentBase{

	public CorpoNegroExperiment(IConfigurationRetriever configurationRetriever,
			IBoardBaseController boardController) {
		super(configurationRetriever, boardController);
		// TODO Auto-generated constructor stub
	}

	
	@Override
	public void initialize(){
		putWidget(new VerticalPanel());
	}
	
	@Override
	public JSONValue getInitialData() {
		return null;

	}
	
	@Override
	public void queued(){
		putWidget(new VerticalPanel());
	}
	
    @Override
    public void start(int time, String initialConfiguration) {

    	final JSONValue value = JSONParser.parseStrict(initialConfiguration);
    	final JSONObject obj = (JSONObject)value;
    	
		final MainPanel mainPanel = new MainPanel();
    	 
		// Configure the camera
		final WlWebcam camera = mainPanel.getWebcam();
		
		camera.setUrl("http://weblabduino.pucsp.br/webcam/cna/image.jpg");
		camera.setStreamingUrl("http://weblabduino.pucsp.br/webcam/cna/video.mjpeg",320,240);
		camera.configureWebcam(obj);
		camera.start();
		addDisposableWidgets(camera);
		
		final WlWebcam camera2 = mainPanel.getWebcam2();
		camera2.setUrl("http://weblabduino.pucsp.br/webcam/cna/image2.jpg");
		camera2.setStreamingUrl("http://weblabduino.pucsp.br/webcam/cna/video2.mjpeg",320,240);
		camera2.configureWebcam(obj);
		camera2.start();
		addDisposableWidgets(camera2);
		
		//Grafico gerado no Xively para o sensor de monoxido de carbono 
		final WlStreamImage graficoPNGTemperatura = mainPanel.getGraficoTemperatura();
		graficoPNGTemperatura.setUrl("https://api.cosm.com/v2/feeds/107050970/datastreams/sensor_temperatura.png");
		graficoPNGTemperatura.configureImageStream(obj);
		graficoPNGTemperatura.start();
		addDisposableWidgets(graficoPNGTemperatura);		
				
		// Configure the timer
		final WlTimer timer = mainPanel.getTimer();
		timer.updateTime(time);
		addDisposableWidgets(timer);	
		
		
		final WlSwitch controlarLampada = mainPanel.getControlarLampada();
		
		this.putWidget(mainPanel);

		
		controlarLampada.addActionListener(new IWlActionListener() {
			
			@Override
			public void onAction(IWlWidget widget) {
				CorpoNegroExperiment.this.boardController.sendCommand("1");
			}
		});
		
				
	}
    
	
}

/* Useful commands
 * 
 *  boardController.sendCommand
 *  
 *  putWidget
 *  addDisposableWidgets
 * */
 