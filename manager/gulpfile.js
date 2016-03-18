var gulp = require("gulp");
var rename = require("gulp-rename");
var cssmin = require("gulp-cssmin");
var jsmin = require('gulp-jsmin');
var concatcss = require("gulp-concat-css");
var concatjs = require("gulp-concat");

gulp.task("build", function() {
    gulp.src("css/*.css")
        .pipe(concatcss("style.css"))
        .pipe(cssmin())
        .pipe(rename({ suffix: ".min" }))
        .pipe(gulp.dest("dist/"));
});