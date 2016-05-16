angular.module("field.manager", [])
    .factory("field", ["$http", function ($http) {
        function Field() {
            var self = this;

            this.data = createField(32, 8, 0);
            this.initialData = createField(32, 8, 0);

            this.mouseState = 0; //1 - pressed, 0 - released
            this.resetMouse = function () {
                self.mouseState = 0;
            };
            this.onHover = function (e, i, j) {
                if (self.mouseState) {
                    toggleCell(i, j);
                }
            };
            this.onMousedown = function (e, i, j) {
                self.mouseState = 1;
                toggleCell(i, j);
            };
            this.onMouseup = function (e, i, j) {
                self.mouseState = 0;
            };
            this.flashData = function () {
                for (var i = 0; i < self.data.length; i++) {
                    for (var j = 0; j < self.data[i].length; j++) {
                        if (self.data[i][j] === 1) {
                            setTimeout((function (i, j) {
                                sendSignal(7 - i, j);
                            })(i, j), 250)
                        }
                    }
                }
            };
            this.revertData = function (e) {
                self.mouseState = 0;
                for (var i = 0; i < self.data.length; i++) {
                    for (var j = 0; j < self.data[i].length; j++) {
                        self.data[i][j] = self.initialData[i][j];
                    }
                }
            };
            this.clearData = function (e) {
                self.mouseState = 0;
                sendSignal(7, 0);
                if (self.data[7][0] == 1) {
                    sendSignal(7, 0);
                }
                for (var i = 0; i < self.data.length; i++) {
                    for (var j = 0; j < self.data[i].length; j++) {
                        self.data[i][j] = 0;
                    }
                }
            };
            this.setData = function (matrix) {
                self.mouseState = 0;
                for (var i = 0; i < self.data.length; i++) {
                    for (var j = 0; j < self.data[i].length; j++) {
                        self.data[i][j] = matrix[i][j];
                    }
                }
                self.initialData = matrix;
            };
            function createField(x, y, initialValue) {
                var data = new Array(y);
                for (var i = 0; i < data.length; i++) {
                    data[i] = new Array(x);
                    data[i].fill(initialValue);
                }
                return data;
            }
            function toggleCell(i, j) {
                var currentCellState = self.data[i][j];
                self.data[i][j] = Math.abs(currentCellState - 1);
                sendSignal(i, j);
            }
            function sendSignal(i, j) {
                $http.get("/set?x=" + j + "&y=" + i)
                    .then(function () { }, function () { });
            }
        };
        return new Field();
    }]);