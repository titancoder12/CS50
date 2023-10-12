# TeamCportz
#### Video Demo:  https://youtu.be/jiwf3MeQv3g
#### Description:
My CS50 Final Project is a team sports app called TeamCportz. TeamCportz helps coaches and managers manage their players and staff by showing who is on their team. TeamCportz allows people to switch teams and create new teams, and also change their very own personal profile. Their personal profile includes information such as their first name, last name, age, role, and their team id. TeamCportz also includes basic functionalities such as login, logout, and register.

TeamCportz is written using the framework Flask. It features the languages Python, HTML, CSS, and JSON. TeamCportz’s structure features a front end (written with flask in app.py), and a back end (also written with flask and with flask_RESTful in main.py). I chose to use a dictionary as a mock-up database instead of one with SQLite because I felt that it would be more straightforward for a prototype.

When a user logs into TeamCportz, they are redirected to the homepage, which contains a message saying exactly “This site is still in Alpha stage
” in header one, and underneath it “Some functionalities may not be available yet, and some bugs may occur.” in header two. From there, if the user clicks on Teams, they will be shown a list of players on the current team that the user is on. If the user clicks on My Account, they will be shown a form that has the default values of the current values of the form. Underneath, there is a button that says ‘Update’.


The Project is composed of the following files:

app.py:
This is the front end code. It is written with Python in Flask. The file includes URLs for the various pages of the app. It includes logic to handle logging in and logging out

main.py:
This is the code for the API or the back end. It is written with Python in Flask and flask_RESTful. It handles get, put, and patch (basically update) for both classes Person and Team.

account.html:
This is the template for the account information. It is written in Jinja and HTML.

apology.html
This is the template for error messages. It is written in Jinja and HTML.

home.html
This is the template for the homepage. It is written in Jinja and HTML.

layout.html
This is the layout that the templates follow. It is written in Jinja and HTML.

login.html
This is the template for the login page. It is written in Jinja and HTML.

register.html
This is the template for the register page. It is written in Jinja and HTML.

teams.html
This is the template for the teams page. It is written in Jinja and HTML.



I intend to continue development of TeamCportz to the extent that my baseball team could make use of it. I would like to add a database to the web application. Some features I look forward to making are a calendar feature, a batting lineup feature, and a chat function. I also want to expand this application into other platforms such as iphone, android, etc.






