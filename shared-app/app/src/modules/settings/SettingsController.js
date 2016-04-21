angular.module('settings')
	.controller('SettingsController', [
		'SettingsService',
		'HeaderService',
		'ToastService',
		SettingsController
	]);


function SettingsController(SettingsService, HeaderService, ToastService) {
	"use strict";

	var self = this;
	self.server = {
		domain: ""
	};
	self.initialize = initialize;
	self.reset = reset;
	self.connect = connect;

	self.initialize();

	function initialize() {
		HeaderService.setTitle("Settings");
		self.server.domain = SettingsService.getDomain();
	}

	function reset() {
		SettingsService.reset();	
	}

	function connect() {
		ToastService.showSuccess('Server connect');
		SettingsService.setDomain(self.server.domain)
	}
};