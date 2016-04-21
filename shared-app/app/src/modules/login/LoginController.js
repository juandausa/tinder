angular.module('login')
    .controller('LoginController', [
        '$state', '$q', 'LoginService',
        LoginController
    ]);

/**
 * Login Controller
 * @param $scope
 * @constructor
 */
function LoginController($state, $q, LoginService) {
    var self = this;
    self.initialize = initialize;
    self.register = register;
    self.login = login;

    self.error = {
        loginLabelStatus: "",
        status: false
    };


    self.data = {
        userName: "",
        password: "",
        remember: false
    }


    self.initialize();

    /* Private functions*/
    function initialize() {
        /* Redirect to login view if no get session*/
        if (!LoginService.isLogged() || !LoginService.isValidSession()) {
            console.log("Login")
            $state.go("login");
        }
        self.data.userName = LoginService.getUserName();
        self.data.password = LoginService.getPassword();
        // self.data.remember = (!angular.isUndefined($cookies.remember)) ? $cookies.remember : "";      
    }

    function register() {
        //$state.go("user");
    }


    function login() {
        console.log(self.data)
        console.log(LoginService.data)
        LoginService.setData(self.data);
        if (LoginService.login()){
            $state.go("home");
        }else{
            //Show error
            alert("error")
        }
    }
}