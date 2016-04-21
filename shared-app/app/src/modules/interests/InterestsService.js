angular.module('interests')
.factory("InterestsService", InterestsService);

InterestsService.$inject = ['$q','RequestService'];

  /**
   * @returns {{InterestsService: InterestsService}}
   * @constructor
   */
function InterestsService($q, RequestService){
  'use strict';

  var _data = {  
     
  };
  
  
  /**
   * @returns  {{deferred.promise}}
   * @constructor
   */
  var _getInterests = function(){
    var url = "/interests/";
    var deferred  = $q.defer();
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
          deferred.reject(response);
      }
    ); 
    return deferred.promise;
  }

/**
   * @returns  {{deferred.promise}}
   * @constructor
   */
  var _createInterest = function(data){
    var url = "/interests/";
    var args = {
      "interest": { 
          "category": data.category, 
          "value": data.value 
      } 
    }
    var deferred  = $q.defer();
    var requestArgs = {
      "method": "POST",
      "url": url,
      "data": args
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
    getInterests: function() {
      return _getInterests();
    },
    createInterest: function(data){
      return _createInterest(data);
    }
  };
}


