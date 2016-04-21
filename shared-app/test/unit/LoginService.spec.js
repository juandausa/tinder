'use strict';

describe('unit test valida que LoginService', function () {
	/* Preparación del ambiente*/
	var loginService;
	beforeEach(function () {
		module('login');
		 inject(['LoginService', function (LoginService) {
                loginService = LoginService;
            }
        ]);

	 });

	/* Test para verificar estado del servicio al iniciar*/
 	describe('al iniciar', function () {
 		it('debe iniciar con userName en blanco', inject(function () {
    		expect(loginService.getUserName()).toEqual('');
	 	}));
		it('debe iniciar con password en blanco', inject(function () {
    		expect(loginService.getPassword()).toEqual('');
	 	}));


 	}); 	


});
