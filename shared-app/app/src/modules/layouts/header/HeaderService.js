myApp.factory("HeaderService", HeaderService);

HeaderService.$inject = [];

function HeaderService() {
	

	var data = {
		title: "",
		input: "",
		progressBarActive: false
	};

	var _setTitle = function(title) {
	 	data.title = title;
	};

	var _hideProgressBar = function(){
		data.progressBarActive = false;
	}

	var _showProgressBar = function(){
		data.progressBarActive = true;
	}

  	return {
  		data: data,
  		getTitle: function(){
			return data.title;
  		},
		setTitle: function(title){
			return _setTitle(title);
		},
		getInput: function(){
			return data.input;
		},
		hideProgressBar: function(){
			return _hideProgressBar();
		},
		showProgressBar: function(){
			return _showProgressBar();
		}

  	};
}