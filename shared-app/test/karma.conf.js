module.exports = function (config) {
  var configuration = {

    basePath: '../',

    files: [
      'app/lib/angular/angular.js',
      'app/lib/angular-animate/angular-animate.js',
      'app/lib/angular-aria/angular-aria.js',
      'app/lib/angular-mocks/angular-mocks.js',
      'app/lib/angular-material/angular-material.js',
      'app/lib/angular-ui-router/release/angular-ui-router.js',
      'app/lib/angular-cookies/angular-cookies.js',
      'app/src/modules/login/*.js',
      'test/unit/**/*.js'
    ],

    logLevel: config.LOG_ERROR,
    port: 9876,
    reporters: ['progress'],
    colors: true,

    autoWatch : false,
    singleRun : true,

    // For TDD mode
    //autoWatch : true,
    //singleRun : false,

    frameworks: ['jasmine'],
    browsers: ['Chrome'],

    customLaunchers: {
      Chrome_travis_ci: {
        base: 'Chrome',
        flags: ['--no-sandbox']
      }
    },

     plugins: [
      'karma-chrome-launcher',
      'karma-jasmine',
      'karma-junit-reporter',
      'karma-coverage'
    ],
    junitReporter: {
        outputFile: 'test/test_reports/junit/junit.xml',
        suite: 'unit'
    },
    preprocessors: {
        'app/src/modules/login/**/*.js': ['coverage']
    },
    coverageReporter: {
        dir: 'test/test_reports/coverage/',            
        reporters: [
            {type: 'lcov', subdir: '.'},
            {type: 'cobertura', subdir: '.', file: 'cobertura.xml'}
        ]
    }
  };
  if(process.env.TRAVIS){
    configuration.browsers = ['Chrome_travis_ci'];
  }
    config.set(configuration);
};