var app = angular.module("ledpad-manager", ["ui.router", "field.manager"]);

app.config([
    '$stateProvider',
    '$urlRouterProvider',
    '$locationProvider',
    function($stateProvider, $urlRouterProvider, $locationProvider) {
        $stateProvider
            .state('index', {
                url: '/',
                templateUrl: 'views/home.html',
                controller: 'HomeController'
            });
        $urlRouterProvider.otherwise('/');
        //$locationProvider.html5Mode(true);
    }
]);
