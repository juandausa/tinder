angular.module('home', [ 'ngMaterial'])
.config(function($mdIconProvider) {
  $mdIconProvider.defaultIconSet('../../app/assets/img/icons/mdi.svg');
});