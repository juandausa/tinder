angular.module('login')
    .factory('LoginService', ['$q', '$cookies', LoginService]);

/**
 * @returns {{isLogged: Function}}
 * @constructor
 */
function LoginService($q, $cookies, RequestService) {
    'use strict';
    var _data = {
        userName: "",
        password: "",

    }
    var userDefault = {
        userName: "admin",
        password: "admin"
    }

    /* Check cookies*/
    var _isLogged = function() {
        return (!angular.isUndefined($cookies.isLogged) && ($cookies.isLogged));
    }

    /* Check session*/
    var _isValidSession = function() {
        var requestArgs = {};
        return RequestService.callApi(requestArgs);
    }

    var _login = function() {
        var isValid = false; 
        if (_data.userName == userDefault.userName && _data.password == userDefault.password){
            $cookies.userName = _data.userName;
            $cookies.password = _data.password;
            isValid = true;
        }
        return isValid;
    }

    var _getUserName = function() {
        return (!angular.isUndefined($cookies.userName)) ? $cookies.userName : _data.userName;
    }

    var _getPassword = function() {
        return (!angular.isUndefined($cookies.password)) ? $cookies.password : _data.password;
    }

    var _logout = function() {
        console.log("logout")
        delete $cookies["isLogged"];
        delete $cookies["userName"];
        delete $cookies["password"];
        delete $cookies["remember"];
    }

    return {
        setData: function(data){
            _data = data
        },
        getUserName: function() {
            return _getUserName();
        },
        getPassword: function() {
            return _getPassword();
        },
        isLogged: function() {
            return _isLogged();
        },
        isValidSession: function() {
            return _isValidSession();
        },
        logout: function() {
            return _logout();
        },
        login: function() {
            return _login();
        }
    };
}