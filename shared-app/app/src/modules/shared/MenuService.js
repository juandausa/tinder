angular.module('shared')
.factory("MenuService", MenuService);

MenuService.$inject = ['$filter'];

function MenuService($filter) {
	
	var data = {
		defaultUserInterests : [
	        {   
	            name:"music/band",
	            icon:"music-note"
	        },
	        {   
	            name:"sport",
	            icon:"soccer"
	        },
	        {   
	            name:"sex",
	            icon:"fire"
	        },
	        {   
	            name:"outdoors",
	            icon:"weather-sunny"
	        },
	        {   
	            name:"travel",
	            icon:"airballoon"
	        },
	        {   
	            name:"food",
	            icon:"food"
	        },
	        {   
	            name:"excercise",
	            icon:"soccer"
	        }
	    ],
	    menuOptions: [
		    {
		      "name": "Edit",
		      "action": "edit",
		      "icon": "border-color"
		    },
		    {
		      "name": "Delete",
		      "action": "delete",
		      "icon": "delete"
		    }
		  ],
	};

	var _searchArrayByObjectProperty = function(array,keySearch,keyReturn,valueToEvalue){
		var returnValue = undefined;
		for (var i = 0; i < array.length; i++) {
		    if (array[i][keySearch] === valueToEvalue) {
				returnValue = array[i][keyReturn];
		      	return returnValue;
		    }
		}
		return returnValue;
	}

	var _addNewCategory = function(interest,categories){
		var category = {};
		category.name = interest.category;
  		category.icon = _searchArrayByObjectProperty(data.defaultUserInterests,"name","icon",interest.category);
  		category.interests = [];
  		category.interests.push({ value: interest.value});
  		categories.push(category);
	}
	var _addToExistenCategory = function(interest,categories){
		var index = categories.map(function(e) { return e.name; }).indexOf(interest.category)
		categories[index].interests.push({ value: interest.value});
	}

	var _getCategories = function(interests){
		
		var categories = [];
		angular.forEach(interests, function(interest, key) {
		  	if (categories.length == 0){
		  		_addNewCategory(interest,categories);
		  	} else {
		  		if (_searchArrayByObjectProperty(categories,"name","name",interest.category) != undefined){
		  			_addToExistenCategory(interest,categories);
		  		} else {
		  			_addNewCategory(interest,categories);
		  		}
		  	}
		  	
		});
		return categories;
	}

  	return {  		
  		getCategories: function(interests){
  			return _getCategories(interests);
  		},  		
  		getMenuOptions: function(){
  			return data.menuOptions;  			
  		}
  	};
}