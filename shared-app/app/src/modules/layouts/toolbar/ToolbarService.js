myApp.factory("ToolbarService", ToolbarService);

ToolbarService.$inject = [];

function ToolbarService() {
	
	var config = {
		isAvailable : false
	};

	var data = {
		title: ""
	};

	var _initialize = function(){
		data.title = "";
	}

	var _isAvailable = function() {
		return config.isAvailable;
	};
	var _show = function() {
		config.isAvailable = true;
	};
	var _hide = function() {
	 	config.isAvailable = false;;
	};
	var _setTitle = function(title) {
	 	data.title = title;;
	};


  	return {
  		initialize: function(){
  			return _initialize();
  		},
		getData: function(){
			return data;
		},
		getConfig: function(){
			return config;
		},
		isAvailable: function(){
			return _isAvailable();
		},
		show: function(){
			return _show();
		},
		hide: function(){
			return _hide();
		},
		setTitle: function(title){
			return _setTitle(title);
		}

  	};
}