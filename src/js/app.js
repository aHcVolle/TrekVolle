var mainsrc = document.createElement('main');
mainsrc.src = 'js/main.js';
document.head.appendChild(mainsrc);

var batterysrc = document.createElement('battery');
batterysrc.src = 'js/battery.js';
document.head.appendChild(batterysrc);

var configurationsrc = document.createElement('configuration');
configurationsrc.src = 'js/configuration.js';
document.head.appendChild(configurationsrc);

var networksrc = document.createElement('network');
networksrc.src = 'js/network.js';
document.head.appendChild(networksrc);


var weathersrc = document.createElement('weather');
weathersrc.src = 'js/weather.js';
document.head.appendChild(weathersrc);