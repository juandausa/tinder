angular.module('shared')
.factory("MapService", MapService);

MapService.$inject = ['$q','NgMap'];

function MapService($q, NgMap) {
    
    var config = {
        map: {},
        marker: {
            draggable:true,
            animation:"Animation.BOUNCE"
        },
        position: {
                latitude:-34.617956, 
                longitude: -58.368990 
            }
    };

    var map = {};
    var marker = {};
    var geocoder = new google.maps.Geocoder;
    var address = {};

    var _setMarker = function(latlng){
        marker = new google.maps.Marker({
                position: latlng,
                map: map,
                draggable: config.marker.draggable,
                animation: config.marker.animation
            });
    }


    var _setGeocode = function(deferred,latlng){
        geocoder.geocode({'location': latlng}, function(results, status) {
            if (status === google.maps.GeocoderStatus.OK) {
              if (results[1]) {

                address = results[1].formatted_address;
                deferred.resolve(address);
              }
            }
          });
    }

    var _initialize = function(location){
        var deferred  = $q.defer();       
        config.position.latitude = location.latitude; 
        config.position.longitude = location.longitude; 
        
        NgMap.getMap().then(function(ngMap) {
            map = ngMap;
            var latlng = new google.maps.LatLng(config.position.latitude, config.position.longitude);
            map.setCenter(latlng);
            _setMarker(latlng);
            _setGeocode(deferred,latlng);
        });       
        return deferred.promise;
    }

    var _setLocation = function(location){
        var deferred  = $q.defer();
        if (location){
            config.position.latitude = location.lat(); 
            config.position.longitude = location.lng(); 
            var latlng = new google.maps.LatLng(config.position.latitude, config.position.longitude);
            map.setCenter(latlng);
            marker.setPosition(latlng);
            _setGeocode(deferred,latlng);
        }
        return deferred.promise;  
    }

    return {
        initialize: function(location){
            return _initialize(location);
        },
        getMap: function(){
            return map;
        }, 
        getMarker: function(){
            return marker;
        },        
        getAddress: function(){
            return address;
        },
        setLocation: function(location){
            return _setLocation(location);
        }
    };
}