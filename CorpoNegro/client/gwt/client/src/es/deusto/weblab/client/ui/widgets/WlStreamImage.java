/*
* Copyright (C) 2005 onwards University of Deusto
* All rights reserved.
*
* This software is licensed as described in the file COPYING, which
* you should have received as part of this distribution.
*
* This software consists of contributions made by many individuals, 
* listed below:
*
* Author: Pablo Orduña <pablo@ordunya.com>
*
*/ 
package es.deusto.weblab.client.ui.widgets;

import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ErrorEvent;
import com.google.gwt.event.dom.client.ErrorHandler;
import com.google.gwt.event.dom.client.LoadEvent;
import com.google.gwt.event.dom.client.LoadHandler;
import com.google.gwt.json.client.JSONObject;
import com.google.gwt.json.client.JSONValue;
import com.google.gwt.user.client.Random;
import com.google.gwt.user.client.Timer;
import com.google.gwt.user.client.ui.HasHorizontalAlignment;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Image;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.ui.Widget;

public class WlStreamImage extends VerticalPanel implements IWlWidget{
	
	public static final String DEFAULT_IMAGE_URL = GWT.getModuleBaseURL() + "/waiting_url_image.jpg";
	public static final int DEFAULT_REFRESH_TIME = 400;
	
	protected Image image;
	
	protected int time;
	protected String url;
	protected String streamingUrl;
	protected int streamingWidth;
	protected int streamingHeight;
	protected Timer timer;
	protected boolean running;
	protected final HorizontalPanel imagePanel;
	
	public WlStreamImage(){
		this(WlStreamImage.DEFAULT_REFRESH_TIME, WlStreamImage.DEFAULT_IMAGE_URL);
	}
	
	public WlStreamImage(int time){
		this(time, WlStreamImage.DEFAULT_IMAGE_URL);
	}
	
	public WlStreamImage(int time, String url){
		this(time, url, WlStreamImage.DEFAULT_IMAGE_URL);
	}
	
	public WlStreamImage(int time, String url, String streamingUrl){
		this.imagePanel = new HorizontalPanel();
		this.imagePanel.setWidth("100%");
		this.imagePanel.setHorizontalAlignment(HasHorizontalAlignment.ALIGN_CENTER);
		this.time         = time;
		this.url          = url;
		this.streamingUrl = streamingUrl;
		
		this.image = new Image(this.getDifferentUrl());
		
		this.imagePanel.add(this.image);
		this.setWidth("100%");
		this.setHorizontalAlignment(HasHorizontalAlignment.ALIGN_CENTER);
		this.add(this.imagePanel);
	}
	
	public void start(){
		this.running = true;
		this.timer = new Timer(){
			@Override
			public void run(){
				WlStreamImage.this.reload();
			}
		};
		this.reload();
	}
	
	public void configureImageStream(JSONObject initialConfigObject) {
		final JSONValue webcamValue = initialConfigObject.get("webcam");
	    if(webcamValue != null) {
	    	final String urlWebcam = webcamValue.isString().stringValue();
	    	setUrl(urlWebcam);
	    }
	}
	
	public void stop(){
		this.running = false;
		if(this.timer != null) 
			this.timer.cancel();
	}
	
	@Override
	public void dispose(){
		this.running = false;
		
		if(this.timer != null)
			this.timer.cancel();
		
		this.timer = null;
	}
	
	@Override
	public void setVisible(boolean visible){
		super.setVisible(visible);
		this.image.setVisible(visible);
	}
	
	public void reload(){
		if(this.running){
			reloadJpeg();
		}
	}

	protected void reloadJpeg() {
		this.image.setUrl(this.getDifferentUrl());
		this.image.addErrorHandler(new ErrorHandler() {
		    
		    @Override
		    public void onError(ErrorEvent event) {
		    	if(WlStreamImage.this.timer != null)
		    		WlStreamImage.this.timer.schedule(WlStreamImage.this.time);
		    }
		});
		this.image.addLoadHandler(new LoadHandler(){
				@Override
				public void onLoad(LoadEvent event) {
					if(WlStreamImage.this.timer != null)
						WlStreamImage.this.timer.schedule(WlStreamImage.this.time);
				}
			}
		);
	}
	
	protected String randomStuff(){
		return "?" + Random.nextInt();
	}
	
	protected String getDifferentUrl(){
		return this.url + this.randomStuff();
	}

	public String getUrl() {
		return this.url;
	}

	public String getStreamingUrl() {
		return this.streamingUrl;
	}
	
	protected void reloadPanel() {
		reload();
	}
	
	public void setTime(int milliseconds) {
		this.time = milliseconds;
		if(this.running) {
			stop();
			start();
		}
	}

	/**
	 * Sets the URL to obtain the webcam image from and reloads the webcam
	 * so as to display that new image.
	 * @param url URL of the image.
	 */
	public void setUrl(String url) {
		this.url = url;
		this.reloadPanel();
	}
	
	/**
	 * Sets the URL to obtain the webcam image in MJPEG format so it 
	 * automatically shows the video stream.
	 * @param url URL of the image.
	 */
	public void setStreamingUrl(String streamingUrl, int width, int height) {
		this.streamingUrl    = streamingUrl;
		this.streamingHeight = height; 
		this.streamingWidth  = width; 
		this.reloadPanel();
	}
	
	@Override
	public Widget getWidget(){
		return this;
	}
}
