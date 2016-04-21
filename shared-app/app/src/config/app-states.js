myApp.config(function($stateProvider, $urlRouterProvider){
	"use strict";
	$stateProvider
		.state('login', {
			url: '/login',
			templateUrl: '../app/src/modules/login/view/login.html'
		})
		.state('users', {
			url: '/users',
			templateUrl: '../app/src/modules/users/view/users.html'
		})
		.state('home', {
			url: '/home',
			templateUrl: '../app/src/modules/home/view/home.html'
		})
		.state('settings', {
			url: '/settings',
			templateUrl: '../app/src/modules/settings/view/settings.html'
		})
		.state('user', {
        	url: "/user/:userId",
        	templateUrl: '../app/src/modules/user/view/user.html'
    	})
    	.state('interests', {
        	url: "/interests",
        	templateUrl: '../app/src/modules/interests/view/interests.html'
    	});
	$urlRouterProvider.otherwise('/login');
});