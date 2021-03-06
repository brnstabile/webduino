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

package es.deusto.weblab.client.experiments.miniestacaometeorologica.ui;

import com.google.gwt.core.client.GWT;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Image;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.Widget;
import com.google.gwt.uibinder.client.UiField;

import es.deusto.weblab.client.ui.widgets.WlWebcam;
import es.deusto.weblab.client.ui.widgets.WlTimer;

import com.google.gwt.user.client.ui.VerticalPanel;
import es.deusto.weblab.client.ui.widgets.WlWebcamSafariBased;
import com.google.gwt.uibinder.client.UiHandler;
import com.google.gwt.event.logical.shared.AttachEvent;
import com.google.gwt.user.cellview.client.CellTable;
import com.google.gwt.user.client.ui.TabPanel;

public class MainPanel extends Composite {

	private static MainPanelUiBinder uiBinder = GWT
			.create(MainPanelUiBinder.class);

	@UiField WlTimer timer;
	@UiField VerticalPanel widget;
	@UiField VerticalPanel main;
	@UiField(provided = true) WlWebcam GraficoTemperatura;
	@UiField(provided = true) WlWebcam GraficoCO2;
	@UiField(provided = true) WlWebcam GraficoLuz;
	@UiField(provided = true) WlWebcam GraficoSom;
	@UiField(provided = true) WlWebcam camera;
	@UiField(provided = true) WlWebcam GraficoHumidade;
	@UiField TabPanel graficos;


	interface MainPanelUiBinder extends UiBinder<Widget, MainPanel> {
	}

	public MainPanel() {
		this.camera = GWT.create(WlWebcam.class);
		this.GraficoHumidade = GWT.create(WlWebcam.class);
		this.GraficoTemperatura = GWT.create(WlWebcam.class);
		this.GraficoCO2 = GWT.create(WlWebcam.class);
		this.GraficoLuz = GWT.create(WlWebcam.class);
		this.GraficoSom = GWT.create(WlWebcam.class);
		initWidget(uiBinder.createAndBindUi(this));

	}

	public WlWebcam getWebcam() {
		return this.camera;
	}
	
	public WlWebcam getGraficoHumidade() {
		return this.GraficoHumidade;
	}
	
	public WlWebcam getGraficoTemperatura() {
		return this.GraficoTemperatura;
	}
	
	public WlWebcam getGraficoCO2() {
		return this.GraficoCO2;
	}
	
	public WlWebcam getGraficoLuz() {
		return this.GraficoLuz;
	}
	
	public WlWebcam getGraficoSom() {
		return this.GraficoSom;
	}

	public WlTimer getTimer(){
		return this.timer;
	}

}
