'use strict'

const switcher = document.querySelector('.btn');

switcher.addEventListener('click', function () {
	// document.body.classList.toggle('dark-theme');

	var className = document.body.className;
    if(className == "light-theme") {
        this.textContent = "Dark";
	  document.body.className = "dark-theme";
    }
    else {
        this.textContent = "Light";
	  document.body.className = "light-theme";
    }

});



function conf (a) {
	if (confirm('sdlsldmal sd?')) {
		// Save it!
		console.log('Thing was saved to the database.');
	    } else {
		// Do nothing!
		console.log('Thing was not saved to the database.');
	    }
}