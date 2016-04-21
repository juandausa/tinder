angular.module('user')
    .controller('UserController', [
        '$state',
        '$stateParams',
        'UserService',
        'HeaderService',
        'MenuService',
        'MapService',
        'ToastService',
        'InterestsService',
        UserController
    ]);

/**
 * User Controller
 * @param $scope
 * @constructor
 */
function UserController($state, $stateParams, UserService, HeaderService, MenuService, MapService, ToastService, InterestsService) {

    var self = this;
    self.user = UserService.getNewUser();
    self.photo_profile = {
        current: undefined,
        changed: undefined,
        show: undefined,
        showOriginalPhoto: true,
        changePhoto: false
    }

    /* Controller functions*/

    self.interest = {};
    self.subInterest = {};
    self.types = "['address']";
    self.address = undefined;
    self.showPhotoOptions = false;

    self.initialize = initialize;
    self.save = save;
    self.getPhotoProfile = getPhotoProfile;
    self.selectPhotoProfile = selectPhotoProfile;
    self.cancelSelectPhotoProfile = cancelSelectPhotoProfile;
    self.savePhotoProfile = savePhotoProfile;
    self.markerClick = markerClick;
    self.selectedItem = null;
    self.searchText = null;
    self.querySearch = querySearch;
    self.selectedInterests = [];
    self.autocompleteDemoRequireMatch = true;
    self.placeChanged = placeChanged;

    /* Inicialize controller*/
    self.initialize($stateParams.userId);

    function initialize(userId) {
        HeaderService.setTitle("User");
        HeaderService.showProgressBar();
        if (userId != "") {            
            inicializeUser(userId);
        } else {
            inicializeNewUser();
        }
        loadInterests();
    }

    /* Private functions*/


    function inicializeUser(userId) {
        UserService.getUser(userId).then(
            function succes(response) {
                HeaderService.hideProgressBar();
                self.showPhotoOptions = true;
                self.user = response.user;
                self.photo_profile.current = self.user.photo_profile;
                self.photo_profile.show = self.photo_profile.current;
                self.photo_profile.showOriginalPhoto = (self.user.photo_profile != "");
                self.selectedInterests = self.user.interests;
                MapService.initialize(self.user.location).then(
                    function(response){
                        self.address = response
                    }
                );
            },
            function(response) {
                HeaderService.hideProgressBar();
                ToastService.showError('Error');

            }
        );
    }

    function inicializeNewUser() {
        //New user            
        HeaderService.hideProgressBar();
        self.showPhotoOptions = false;
        self.photo_profile.current = "";
        self.photo_profile.show = "";
        self.photo_profile.showOriginalPhoto = (self.user.photo_profile != "");
        var location
        if (navigator.geolocation) {
            navigator.geolocation.watchPosition(
                function(position) {
                    self.user.location.latitude = position.coords.latitude;
                    self.user.location.longitude = position.coords.longitude;
                    MapService.initialize(self.user.location);
                    
                });
        } else {
                    MapService.initialize(self.user.location);
        }
    }


    function save() {
        self.user.interests = self.selectedInterests.map(function(int) {
            var value = {}
            value.category = int.category;
            value.value = int.value;
            return value;
        });
        UserService.save(self.user).then(
            function succes(response) {
                ToastService.showSuccess('User save');
                // Parche porque el API no retorna el userId
                if (self.user.id == undefined){
                    $state.go("users");
                } else {
                    UserService.getUser(self.user.id).then(
                        function succes(response) {
                            HeaderService.hideProgressBar();
                            self.user = response.user;
                            self.photo_profile.current = self.user.photo_profile;
                            self.photo_profile.show = self.photo_profile.current;
                            self.photo_profile.showOriginalPhoto = (self.user.photo_profile != "");
                            self.selectedInterests = self.user.interests;
                            MapService.initialize(self.user.location).then(
                                function(response){
                                    self.address = response
                                }
                            );

                        },
                        function(response) {
                            HeaderService.hideProgressBar();
                            ToastService.showError('Error');

                        }
                    );
                }
            },
            function error(response) {}
        );
    }


    function getPhotoProfile() {
        return self.photo_profile.show;
    }

    function selectPhotoProfile($file, $event, $flow) {
        self.photo_profile.changePhoto = true;
        var fileReader = new FileReader();
        fileReader.onload = function(event) {
            self.photo_profile.changed = event.target.result;
            self.photo_profile.showOriginalPhoto = false;
            self.photo_profile.show = self.photo_profile.changed;
        };
        fileReader.readAsDataURL($file.file);
    }

    function cancelSelectPhotoProfile($file, $flow) {
        self.photo_profile.show = self.photo_profile.current;
        self.photo_profile.showOriginalPhoto = true;
        self.photo_profile.changePhoto = false;
    }


    function savePhotoProfile() {
        self.user.photo_profile = self.photo_profile.show;
        UserService.savePhotoProfile(self.user).then(
            function succes(response) {
                self.photo_profile.changePhoto = false;
                ToastService.showSuccess('Profile photo save')
            },
            function error(response) {
                ToastService.showError('Profile photo save error')
            });
    }

    function markerClick(e) {
        MapService.setLocation(MapService.getMarker().getPosition()).then(
            function(response){
                self.address = response
            }
        );
        self.user.location.latitude = MapService.getMarker().getPosition().lat();
        self.user.location.longitude = MapService.getMarker().getPosition().lng();
    }

     function placeChanged() {
        self.place = this.getPlace();
        MapService.setLocation(self.place.geometry.location).then(
            function(response){
                self.address = response
            }
        );
        self.user.location.latitude = self.place.geometry.location.lat();
        self.user.location.longitude = self.place.geometry.location.lng();
      }
    /**
     * Search for vegetables.
     */
    function querySearch(query) {
        var results = query ? self.interests.filter(createFilterFor(query)) : [];
        return results;
    }

    /**
     * Create filter function for a query string
     */
    function createFilterFor(query) {
        var lowercaseQuery = query;
        return function filterFn(interest) {
            return (interest.category.indexOf(lowercaseQuery) === 0) ||
                (interest.value.indexOf(lowercaseQuery) === 0);
        };

    }

    function loadInterests() {
        InterestsService.getInterests().then(
            function succes(response) {
                self.interests = response.interests;                
            },
            function error(response) {
                ToastService.showError('Server error');
            }
        );


    }
}