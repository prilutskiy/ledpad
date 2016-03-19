var app = angular.module("ledpad-manager", ["ui.router"]);

app.config([
    '$stateProvider',
    '$urlRouterProvider',
    '$locationProvider',
    function($stateProvider, $urlRouterProvider, $locationProvider) {
        $stateProvider
            .state('index', {
                url: '/',
                templateUrl: 'pages/home.html',
                controller: 'homeController'
            });
        $urlRouterProvider.otherwise('/');
        //$locationProvider.html5Mode(true);
    }
]);

app.controller('startupController', function($scope) {
    $scope.range = function(min, max, step) {
        step = step || 1;
        var input = [];
        for (var i = min; i <= max; i += step) {
            input.push(i);
        }
        return input;
    };
    $scope.field = new Array(32);
    for (var i = 0; i < $scope.field.length; i++) {
        $scope.field[i] = new Array(32);
        $scope.field[i].fill(0);
    }
});

app.controller('homeController', function($scope) {
    var toggleCell = function(i, j) {
        var currentCellState = $scope.field[i][j];
        $scope.field[i][j] = Math.abs(currentCellState - 1);
    }
    $scope.mouseState = 0; //1 - pressed, 0 - released
    $scope.resetMouse= function(){
        $scope.mouseState = 0;  
    };
    $scope.onHover = function(e, i, j) {
        if ($scope.mouseState) {
            toggleCell(i, j);
        }
    };
    $scope.onMousedown = function(e, i, j) {
        $scope.mouseState = 1;
        toggleCell(i, j);
    };
    $scope.onMouseup = function(e, i, j) {
        $scope.mouseState = 0;
    };
});