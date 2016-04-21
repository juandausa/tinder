myApp.controller('SideNavController', SideNavController);

SideNavController.$inject = ['$mdSidenav', '$stateParams', '$state'];

function SideNavController($mdSidenav, $stateParams, $state){
  	"use strict";

  	var self = this;

	self.options = [
		{name:"home", url:"home", icon:"home"}, 
    {name:"settings", url:"settings", icon:"settings"},
		{name:"users", url:"users", icon:"account"},
	];

	self.selectOption   = selectOption;
  self.toggleList  = toggleList;

    /**
     * Hide or Show the 'left' sideNav area
     */
    function toggleList() {
      $mdSidenav('left').toggle();
    }
    
	function selectOption (option) {
    	console.log(option.url);
    	$state.go(option.url); 
    }

}



