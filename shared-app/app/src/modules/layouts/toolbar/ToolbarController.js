myApp.controller('ToolBarController', ToolBarController);

ToolBarController.$inject = ['$stateParams', '$state','ToolbarService'];

function ToolBarController($stateParams, $state, ToolbarService){
	
	"use strict";
	var self = this;
	self.data = ToolbarService.getData();
	self.toolbarConfig = ToolbarService.getConfig(); 
	self.initialize = initialize;
	self.clear = clear;
	self.search = search;
    
	self.initialize();

    function initialize(){
		ToolbarService.initialize();
    }
    
	function clear(){
		self.input = "";
	}

	function search(){
		console.log(search)
	}
}