angular.module('users')
.factory("UsersService", UsersService);

UsersService.$inject = ['$q','RequestService'];

  /**
   * @returns {{isLogged: Function}}
   * @constructor
   */
function UsersService($q, RequestService){
  'use strict';

  var _data = {};
  var _getUsers = function(){
    var deferred  = $q.defer();
    var requestArgs = {
      "method": "GET",
      "url": "/users"
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
  return {
    data: _data,
    getUsers: function() {
      return _getUsers();
    }
  };
}


