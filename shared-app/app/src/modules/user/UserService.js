angular.module('user')
	.factory("UserService", UserService);

UserService.$inject = ['$q', 'RequestService'];

/**
 * @returns {{UserService: UserService}}
 * @constructor
 */
function UserService($q, RequestService) {
	'use strict';

	var _data = {
		"user": {
			"name": "",
			"alias": "",
			"email": "",
			"location": {
				"latitude": -34.745145,
				"longitude": -58.259107
			},
			"interests": [

			],
			"photo_profile": ""
		}
	};
	var config = {
		"url": "/users",
		"method": "POST",
		"data": {}
	}
	var _mode = {
		USER: "U",
		PHOTO: "P"
	};

	/**
	 * @returns {{_data}}
	 * @constructor
	 */
	var _getNewUser = function() {
		return _data.user;
	}

	/**
	 * @returns {{config}}
	 * @constructor
	 */
	var _getRequestConfig = function(mode, user) {
		if (mode == _mode.USER) {
			config.data = { user: user }
			if (user.id != undefined) {
				config.url = "/users/" + user.id;
				config.method = "PUT";
				config.data.metadata = {"version": "0.1"};
			}
		} else if (mode == _mode.PHOTO) {
			config.method = "PUT";
			config.url = "/users/" + user.id + "/photo";
			config.data = { photo: user.photo_profile }
		}

		var requestArgs = {
			method: config.method,
			url: config.url,
			data: config.data
		};
		return config;
	}

	/**
	 * @returns  {{deferred.promise}}
	 * @constructor
	 */
	var _save = function(user) {
		var requestArgs = _getRequestConfig(_mode.USER, user)
		var deferred = $q.defer();

		RequestService.callApi(requestArgs)
			.then(
				function successCallback(response) {
					deferred.resolve(response);
				},
				function errorCallback(response) {
					deferred.reject(response);
				}
			);
		return deferred.promise;

	}

	/**
	 * @returns  {{deferred.promise}}
	 * @constructor
	 */
	var _getUser = function(userId) {
		var url = "/users/" + userId;
		var deferred = $q.defer();
		var requestArgs = {
			"method": "GET",
			"url": url
		};
		RequestService.callApi(requestArgs)
			.then(
				function successCallback(response) {
					deferred.resolve(response);
				},
				function errorCallback(response) {
					_data = {};
					deferred.reject(response);
				}
			);
		return deferred.promise;
	}


	/**
	 * @returns  {{deferred.promise}}
	 * @constructor
	 */
	var _savePhotoProfile = function(user) {
			console.log(user)
			var requestArgs = _getRequestConfig(_mode.PHOTO, user)
			var deferred = $q.defer();

			RequestService.callApi(requestArgs)
				.then(
					function successCallback(response) {
						deferred.resolve(response);
					},
					function errorCallback(response) {
						deferred.reject(response);
					}
				);
			return deferred.promise;
		}
		/**
		 * @returns  {{deferred.promise}}
		 * @constructor
		 */
	var _delete = function(userId) {
		var url = "/users/" + userId;
		var deferred = $q.defer();
		var requestArgs = {
			"method": "DELETE",
			"url": url
		};
		RequestService.callApi(requestArgs)
			.then(
				function successCallback(response) {
					deferred.resolve(response);
				},
				function errorCallback(response) {
					deferred.reject(response);
				}
			);
		return deferred.promise;
	}

	return {
		getUser: function(userId) {
			return _getUser(userId);
		},
		getNewUser: function() {
			return _getNewUser();
		},
		save: function(user) {
			return _save(user);
		},
		savePhotoProfile: function(user) {
			return _savePhotoProfile(user);
		},
		delete: function(userId) {
			return _delete(userId);
		}
	};
}