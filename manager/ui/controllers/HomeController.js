app.controller('HomeController', [
    "field", "$scope",
    function(field, $scope) {
        $scope.field = field.data;
        
        $scope.resetMouse = field.resetMouse;
        $scope.onHover = field.onHover;
        $scope.onMousedown = field.onMousedown;
        $scope.onMouseup = field.onMouseup;
        
        $scope.clearData = field.clearData;
        $scope.setData = field.setData;
        $scope.revertData = field.revertData;
    }]);