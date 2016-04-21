angular.module('shared')
.factory("ToastService", ToastService);

ToastService.$inject = ['$mdToast'];

function ToastService($mdToast) {
    
    var last = {
        bottom: true,
        top: false,
        left: false,
        right: true
    };

    var TYPE = {
        "ERROR": "error",
        "SUCCESS": "success",
        "INFO": "info"
    }

    var toastPosition = angular.extend({}, last);

    function sanitizePosition() {
        var current = toastPosition;

        if (current.bottom && last.top) current.top = false;
        if (current.top && last.bottom) current.bottom = false;
        if (current.right && last.left) current.left = false;
        if (current.left && last.right) current.right = false;

        last = angular.extend({}, current);
    }

    function getToastPosition() {
        sanitizePosition();

        return Object.keys(toastPosition)
          .filter(function(pos) {
            return toastPosition[pos];
        })
        .join(' ');
    };

    var _showMessage = function(msj,type){
        var pinTo = getToastPosition();
        $mdToast.show(
          $mdToast.simple()
          .textContent(msj)
          .position(pinTo)
          .theme(type + "-toast")
          .hideDelay(3000)
        );
    }

    return {
        showError: function(msj){
            return _showMessage(msj,TYPE.ERROR);
        },
        showSuccess: function(msj){
            return _showMessage(msj,TYPE.SUCCESS);
        },
        showInfo: function(msj){
            return _showMessage(msj,TYPE.INFO);
        }
    };
}