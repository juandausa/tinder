angular.module('shared')
.factory("DialogService", DialogService);

DialogService.$inject = ['$mdDialog'];

function DialogService($mdDialog) {
    
   

    var TYPE = {
        "ERROR": "error",
        "SUCCESS": "success",
        "INFO": "info"
    }

   

    var _showMessage = function(title,content,okMsj,event,type){
        $mdDialog.show(
            $mdDialog.alert()
            .title(title)
            .textContent(content)
            .ok(okMsj)
            .targetEvent(event)
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