angular.module('users')
	.controller('UsersController', [
		'$state',
		'UsersService',
		'UserService',
		'HeaderService',
		'MenuService',
		'ToastService',
		'RequestService',
		UsersController
	]);

/**
 * User Controller
 * @param $scope
 * @constructor
 */
function UsersController($state, UsersService, UserService, HeaderService, MenuService, ToastService, RequestService) {
	"use strict";

	var self = this;

	self.data = {
		users: []
	};

	self.filters = HeaderService.data;
	self.initialize = initialize;
	self.newUser = newUser;
	self.menuClick = menuClick;


	self.initialize();

	function initialize() {
		HeaderService.setTitle("Users");
		HeaderService.showProgressBar();
		self.menuOptions = MenuService.getMenuOptions();
		UsersService.getUsers().then(
			function success(response) {
				self.data.users = response.users;
				angular.forEach(self.data.users,function(value,key){
					var requestArgs = {
		              "method": "GET",
		              "url": value.user.photo_profile
		            };
		            RequestService.callApiCustomUrl(requestArgs)
		            .then(
		              function successCallback(response) {
		                  value.user.photo = response;  
		              }, 
		              function errorCallback(response) {
		              	value.user.photo ="";
		              }
		            );  
		          });

				HeaderService.hideProgressBar();
				ToastService.showSuccess('Users: ' + self.data.users.length);
			},
			function error(response) {
				HeaderService.hideProgressBar();
				ToastService.showError('Server error');
			}
		);
	}

	function newUser() {
		$state.go("user");
	};

	function menuClick(action, data) {
		if (action == "edit") {
			$state.go("user", {
				userId: data.id
			});
		} else if (action == "delete") {
			UserService.delete(data.id).then(
				function success(response) {
					ToastService.showSuccess('User deleted');
					UsersService.getUsers().then(
						function success(response) {
							self.data.users = response.users;
							HeaderService.hideProgressBar();
						},
						function error(response) {
							HeaderService.hideProgressBar();
							ToastService.showError('Server error');
						}
					);
				}
			);
		}
	};
}