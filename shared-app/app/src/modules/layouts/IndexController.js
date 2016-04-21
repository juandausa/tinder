myApp.controller('IndexController', [
        '$mdSidenav',
        '$state',
        'LoginService',
        'ToolbarService',
        IndexController
    ]);


function IndexController($mdSidenav, $state ,LoginService, ToolbarService) {
	"use strict";
       
  var self = this;

  self.toolbar = ToolbarService;
	self.options = {
    user:[
      {name:"home", url:"home", icon:"home"}, 
      {name:"users", url:"users", icon:"account"}
    ],
    system: [
      {name:"Interests", url:"interests", icon:"thumb-up"},
      {name:"Api settings", url:"settings", icon:"settings"},
      {name:"Logout", url:"login", icon:"account"}
    ]
  };

  self.user = {
    name: "Admin",
    email: "admin@sample.com"
  }

	self.selectOption = selectOption;
  self.toggleList   = toggleList;
  self.initialize   = initialize;
  self.showToolbar = showToolbar;
  self.showSideNav = showSideNav;
  self.showHeader = showHeader;

  self.initialize();

  function showToolbar(){
    return ($state.current.name === 'users')
  }
  
  function showSideNav(){
    return !($state.current.name === 'login')
  }

  function showHeader(){
    return !($state.current.name === 'login')
  }
  
  function initialize() {
    if (!LoginService.isLogged()){
      console.log("Isn't logged");
      $state.go("login");
    }
    self.toolbar.initialize();
  }
  /**
   * Hide or Show the 'left' sideNav area
   */
  function toggleList() {
    $mdSidenav('left').toggle();
  }
    
  function selectOption (option) {
    $state.go(option.url); 
  }


};