import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    shares = db.execute("SELECT * FROM shares WHERE id = ?", user_id)
    temp_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = float(temp_cash[0]["cash"])
    portfolio = []
    for i in range(len(shares)):
        quote = lookup(shares[i]["symbol"])
        portfolio.append(quote)
        num_shares = temp_num_shares[0]["shares"]
        total = float(num_shares) * float(portfolio[i]["price"])
        portfolio[i]["total"] = total
        portfolio[i]["shares"] = num_shares

    grand_total = float(cash)
    for i in range(len(portfolio)):
        grand_total += float(portfolio[i]["total"])
    return render_template("index.html", portfolio=portfolio, cash=cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("shares") or not request.form.get("symbol"):
            return apology("missing shares/symbol")
        elif (request.form.get("shares")).isalpha():
            return apology("number of shares must be numeric", 400)
        elif (float(request.form.get("shares")) % 1) != 0:
            return apology("number of shares must be a whole and non-negative number", 400)
        elif float(request.form.get("shares")) < 0:
            return apology("cannot buy a negative number of shares", 400)

        quote = lookup(str(request.form.get("symbol")))
        user_id = session["user_id"]
        if quote is None:
            return apology("symbol does not exist", 400)

        shares = request.form.get("shares")
        total_value = quote["price"] * float(shares)
        query = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        total_cash = float(query[0]["cash"])
        if total_value > total_cash:
            return apology("not enough cash", 400)
        else:
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_value, user_id)
            if len(db.execute("SELECT id, symbol FROM shares WHERE id = ? AND symbol = ?", user_id, quote["symbol"])) == 0:
                db.execute("INSERT INTO shares (id, symbol, name, shares) VALUES (?, ?, ?, ?)",
                           user_id, quote["symbol"], quote["name"], shares)
            else:
                db.execute("UPDATE shares SET shares = shares + ? WHERE id = ?", shares, user_id)
            db.execute("INSERT INTO log (id, symbol, shares, price, time) VALUES (?, ?, ?, ?, DATETIME('now'))",
                       user_id, quote["symbol"], shares, total_value)
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = []
    user_id = session["user_id"]
    log = db.execute("SELECT * FROM log WHERE id=?", user_id)
    for i in range(len(log)):
        num_shares = log[i]["shares"]
        time = log[i]["time"]
        symbol = log[i]["symbol"]
        price = float(num_shares) * float(log[i]["price"])
        history_temp = {
            "price": price,
            "shares": num_shares,
            "transacted": time,
            "symbol": symbol
        }
        history.append(history_temp)

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quote = lookup(str(request.form.get("symbol")))
        if quote is None:
            return apology("symbol does not exist", 400)
        else:
            return render_template("quoted.html", symbol=quote["symbol"], name=quote["name"], price=quote["price"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password", 400)

        # Ensure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        user_temp = db.execute("SELECT username FROM users WHERE username = ?", request.form.get("username"))
        if len(user_temp) != 0:
            # Ensure username is avalible
            if str(request.form.get("username")) == str(user_temp[0]["username"]):
                return apology("username taken", 400)

        # ensure password is a strong password
        elif len(str(request.form.get("password"))) < 6:
            return apology("password is not strong enough, must have at least 6 letters", 400)

        # Generate hash
        pass_hash = generate_password_hash(request.form.get("password"))

        # Insert username and password
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), pass_hash)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session["user_id"]
    symbols_dict = db.execute("SELECT symbol FROM shares WHERE id = ?", user_id)
    symbols = []
    for i in range(len(symbols_dict)):
        symbols.append(symbols_dict[i]["symbol"])

    if request.method == "POST":
        if not request.form.get("shares") or request.form.get("symbol") not in symbols:
            return apology("missing shares/symbol", 400)
        elif request.form.get("shares").isalpha():
            return apology("number of shares must be numeric", 400)
        elif (float(request.form.get("shares")) % 1) != 0:
            return apology("number of shares must be a whole and non-negative number", 400)
        elif float(request.form.get("shares")) < 0:
            return apology("cannot sell a negative number of shares", 400)
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        shares_owned_dict = db.execute("SELECT shares FROM shares WHERE id = ? AND symbol = ?", user_id, symbol)
        shares_owned = int(shares_owned_dict[0]["shares"])
        if (shares_owned - shares) < 0:
            return apology("too many shares", 400)
        quote = lookup(symbol)
        value_sold = 0-(float(shares) * float(quote["price"]))
        db.execute("INSERT INTO log (id, symbol, shares, price, time) VALUES (?, ?, ?, ?, DATETIME('now'))",
                   user_id, symbol, shares, value_sold)

        if shares_owned - shares == 0:
            db.execute("DELETE FROM shares WHERE symbol = ? AND id = ?", symbol, user_id)
            return redirect("/")
        else:
            db.execute("UPDATE shares SET shares = shares - ? WHERE id = ? AND symbol = ?", shares, user_id, symbol)
            return redirect("/")
    else:
        return render_template("sell.html", symbols=symbols)
