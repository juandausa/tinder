myApp.controller('HeaderController', HeaderController);

HeaderController.$inject = ['$mdSidenav', '$state', 'HeaderService'];

function HeaderController($mdSidenav, $state, HeaderService){
	"use strict";
	var self = this;
    self.data = HeaderService.data;
    self.toggleList  = toggleList;
    self.isShowSearch  = isShowSearch;
    self.showProgressBar = showProgressBar;
    self.isShowBack = isShowBack;
    self.back = back;
    
    function showProgressBar() {
        return self.data.progressBarActive;
    }

    /**
     * Hide or Show the 'left' sideNav area
     */
    function isShowSearch() {
      // return ($state.current.name === 'users')
      return false;
    }   
    
    function isShowBack() {
        return ($state.current.name !== 'home')
    }   

    function back() {
      // return ($state.current.name === 'users')
      window.history.back();
    }
        /**
     * Hide or Show the 'left' sideNav area
     */
    function toggleList() {
      $mdSidenav('left').toggle();
    }

}