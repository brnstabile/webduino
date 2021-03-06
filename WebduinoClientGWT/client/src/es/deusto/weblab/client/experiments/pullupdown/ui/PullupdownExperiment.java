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

package es.deusto.weblab.client.experiments.pullupdown.ui;

import com.google.gwt.json.client.JSONObject;
import com.google.gwt.json.client.JSONParser;
import com.google.gwt.json.client.JSONValue;
import com.google.gwt.user.client.ui.VerticalPanel;

import es.deusto.weblab.client.configuration.IConfigurationRetriever;
import es.deusto.weblab.client.lab.experiments.IBoardBaseController;
import es.deusto.weblab.client.lab.experiments.UIExperimentBase;
import es.deusto.weblab.client.ui.widgets.WlTimer;
import es.deusto.weblab.client.ui.widgets.WlWebcam;

public class PullupdownExperiment extends UIExperimentBase{

	public PullupdownExperiment(IConfigurationRetriever configurationRetriever,
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
    	
		// 
		// Configure the camera
		final WlWebcam camera = mainPanel.getWebcam();
		camera.setUrl("http://weblabduino.pucsp.br/webcam/pullupdown/image.jpg");
		camera.setStreamingUrl("http://weblabduino.pucsp.br/webcam/pullupdown/video.mjpeg",320,240);
		camera.configureWebcam(obj);
		camera.start();
		addDisposableWidgets(camera);
		
		//Grafico gerado no Xively para o sensor de monoxido de carbono 
		final WlWebcam graficoPNGPullUp = mainPanel.getGraficoPullUp();
		graficoPNGPullUp.setUrl("https://api.cosm.com/v2/feeds/605406634/datastreams/V_LDR_R_Pull_Up.png");
		graficoPNGPullUp.configureWebcam(obj);
		graficoPNGPullUp.start();
		addDisposableWidgets(graficoPNGPullUp);
		
		//Grafico gerado no Xively para o sensor de monoxido de carbono 
		final WlWebcam graficoPNGPullDown = mainPanel.getGraficoPullDown();
		graficoPNGPullDown.setUrl("https://api.cosm.com/v2/feeds/605406634/datastreams/V_R_Pull_Down.png");
		graficoPNGPullDown.configureWebcam(obj);
		graficoPNGPullDown.start();
		addDisposableWidgets(graficoPNGPullDown);

		//
		// Configure the timer
		final WlTimer timer = mainPanel.getTimer();
		timer.updateTime(time);
		addDisposableWidgets(timer);
		
		
		this.putWidget(mainPanel);
	}

	
}

/* Useful commands
 * 
 *  boardController.sendCommand
 *  
 *  putWidget
 *  addDisposableWidgets
 * */
 