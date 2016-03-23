app.controller('StartupController', function($scope) {
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

