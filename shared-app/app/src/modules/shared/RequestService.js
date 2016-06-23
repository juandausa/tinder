angular.module('shared')
.factory("RequestService", RequestService);

RequestService.$inject = ['$http','$q','SettingsService'];

function RequestService($http, $q, SettingsService) {
    
    var data = {};
    var _callApi = function(requestData){
        var deferred  = $q.defer();
        var request = $http({
            method: requestData.method,
            contentType: 'application/json',
            url: SettingsService.getDomain() + requestData.url,
            data: requestData.data
        })
        .success( function(response){
            deferred.resolve(response);     
        })
        
        .error( function(response){
            deferred.reject(response);
        });
        return deferred.promise;
    }

    var _callApiCustomUrl = function(requestData){
        var deferred  = $q.defer();
        var request = $http({
            method: requestData.method,
            contentType: 'application/json',
            url:  requestData.url,
            data: requestData.data
        })
        .success( function(response){
            deferred.resolve(response);     
        })
        
        .error( function(response){
            deferred.reject(response);
        });
        return deferred.promise;
    }
    return {
        data: data,
        callApiCustomUrl: function(requestData){
            return _callApiCustomUrl(requestData);
        },
        callApi: function(requestData){
            return _callApi(requestData);
        }
    };
}