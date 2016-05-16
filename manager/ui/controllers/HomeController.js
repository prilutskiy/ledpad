app.controller('HomeController', [
    "field", "$scope", "$http",
    function (field, $scope, $http) {
        $scope.field = field.data;
        $scope.loadedFile = null;

        $scope.resetMouse = field.resetMouse;
        $scope.onHover = field.onHover;
        $scope.onMousedown = field.onMousedown;
        $scope.onMouseup = field.onMouseup;

        $scope.flashData = field.flashData;
        $scope.clearData = field.clearData;
        $scope.revertData = field.revertData;
        
        $scope.saveData = function (e) {
            var filename = "field.gol";
            var data = JSON.stringify(field.data);
            var blob = new Blob([data], { type: 'text/json' });
            var e = document.createEvent('MouseEvents');
            var a = document.createElement('a');

            a.download = filename;
            a.href = window.URL.createObjectURL(blob);
            a.dataset.downloadurl = ['text/json', a.download, a.href].join(':');
            e.initEvent('click', true, false, window,
                0, 0, 0, 0, 0, false, false, false, false, 0, null);
            a.dispatchEvent(e);
        };
        var f = function (e) {
            var file = e.files[0];
            if (!file) {
                return;
            }
            var reader = new FileReader();
            var f = function (e) {
                var content = e.target.result;
                var data = JSON.parse(content);
                field.setData(data);
                if (!(data || data instanceof Array)) {
                    console.log("Invalid file format");
                }
            };
            reader.onload = f;
            reader.readAsText(file);
            e.value = "";
        };
        $scope.loadData = f;
    }]);