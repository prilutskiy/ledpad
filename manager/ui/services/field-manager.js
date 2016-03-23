angular.module("field.manager", [])
    .factory("field", function() {
        function Field() {
            var self = this;
            this.data = createField(32, 0);
            this.mouseState = 0; //1 - pressed, 0 - released
            this.resetMouse = function() {
                self.mouseState = 0;
            };
            this.onHover = function(e, i, j) {
                if (self.mouseState) {
                    toggleCell(i, j);
                }
            };
            this.onMousedown = function(e, i, j) {
                self.mouseState = 1;
                toggleCell(i, j);
            };
            this.onMouseup = function(e, i, j) {
                self.mouseState = 0;
            };
            this.clearData = function(e) {
                self.mouseState = 0;
                for (var i = 0; i < self.data.length; i++) {
                    for (var j = 0; j < self.data[i].length; j++) {
                        self.data[i][j] = 0;
                    }
                }
            };
            this.setData = function(e, matrix) {
                self.mouseState = 0;
                self.data = matrix;
            };
            function createField(n, initialValue) {
                var data = new Array(n);
                for (var i = 0; i < data.length; i++) {
                    data[i] = new Array(n);
                    data[i].fill(initialValue);
                }
                return data;
            }
            function toggleCell(i, j) {
                var currentCellState = self.data[i][j];
                self.data[i][j] = Math.abs(currentCellState - 1);
            }
        };
        return new Field();
    });