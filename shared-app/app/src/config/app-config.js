myApp.config(function($mdThemingProvider,$mdIconProvider){
  	"use strict";
  	/* Themes */

  
 	$mdThemingProvider.theme('default')
                          .primaryPalette('indigo')
                          .accentPalette('blue');
    $mdThemingProvider.theme("success-toast");
	$mdThemingProvider.theme("error-toast");
	$mdThemingProvider.theme("info-toast");
 	$mdIconProvider.defaultIconSet('../../app/assets/img/icons/mdi.svg')
});

