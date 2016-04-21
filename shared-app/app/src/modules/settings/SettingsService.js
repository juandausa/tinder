angular.module('settings')
.factory("SettingsService", SettingsService);

SettingsService.$inject = ['$cookies'];

function SettingsService($cookies) {
	var heroku = "https://enigmatic-scrubland-75073.herokuapp.com";
	var local = "http://localhost:5000";
	var data = {
		server: {
			domain:"https://enigmatic-scrubland-75073.herokuapp.com"
		}
	};

	/* Init service*/
	_init();

	function _init(){
		data.server.domain = (angular.isUndefined($cookies.get('urlDomain'))) ? heroku : $cookies.get('urlDomain')  ;
	}

	function _setDomain(domain){
		data.server.domain = domain;
  		$cookies.put('urlDomain', domain);
	}

	function _reset(){
		data.server.domain = "";
		$cookies.remove("urlDomain");
	}


  	return {
  		getDomain: function(){
  			return data.server.domain;
  		},
  		setDomain: function(domain){
  			return _setDomain(domain);
  		},
  		reset: function(){
  			return _reset();
  		}
  	};
}