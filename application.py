import os
import re
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Note: I would have configured this code to create a new table per user with all their information, but by the time I remembered you could enter variables as table names it was too late.
#       Besides this is only a small app that will not be used by many people so keeping all the users transactions and stocks on two tables isn't too terribly inefficient.

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    user = session["user_id"]
    img = session["img"]
    cash = db.execute("SELECT cash FROM users WHERE username = :username", username = user)
    row1 = db.execute("SELECT name, symbol, shares FROM stocks WHERE user = :user", user = user)
    overall = 0
    for row in row1:
        response = lookup(row["symbol"])
        total = response["price"] * row["shares"]
        overall += total
        db.execute("UPDATE stocks SET price = :price, total = :total WHERE user = :user AND symbol = :symbol", price = response["price"], total = total, user = user, symbol = row["symbol"])
    rows = db.execute("SELECT name, symbol, price, shares, total FROM stocks WHERE user = :user", user = user)
    overall += cash[0]["cash"]
    return render_template("index.html", rows = rows, cash = cash[0]["cash"], overall = overall, image = img)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    user = session["user_id"]
    img = session["img"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        time = datetime.now()
        response = lookup(symbol)
        if symbol == "/0" or response == "None":
            return apology("Symbol Invalid", 404)
        purchased = db.execute("SELECT count(symbol) AS count FROM stocks WHERE user = :user AND symbol = :symbol", user = user, symbol = symbol)
        cash = db.execute("SELECT cash FROM users WHERE username = :user", user = user)
        total = response["price"] * int(shares)
        newCash = cash[0]["cash"] - total
        if newCash < 0:
            return apology("Insufficient Funds", 400)
        db.execute("UPDATE users SET cash = :cash WHERE username = :user", cash = newCash, user = user)
        if purchased[0]["count"] == 1:
            rows = db.execute("SELECT shares FROM stocks WHERE user = :user AND symbol = :symbol", user = user, symbol = symbol)
            shares += rows[0]["shares"]
            db.execute("UPDATE stocks SET shares = :shares WHERE user = :user AND symbol = :symbol", shares = shares, user = user, symbol = symbol)
            db.execute("INSERT INTO transactions (user, name, symbol, price, shares, time) VALUES (:user, :name, :symbol, :price, :shares, :time)", user = user, name = response["name"], symbol = symbol, price = response["price"], shares = shares, time = time)
            return redirect("/")
        else:
            response = lookup(symbol)
            db.execute("INSERT INTO stocks (user, name, symbol, price, shares, total) VALUES (:user, :name, :symbol, :price, :shares, :total)", user = user, name = response["name"], symbol = symbol, price = response["price"], shares = shares, total = total)
            db.execute("INSERT INTO transactions (user, name, symbol, price, shares, time) VALUES (:user, :name, :symbol, :price, :shares, :time)", user = user, name = response["name"], symbol = symbol, price = response["price"], shares = shares, time = time)
            return redirect("/")
    else:
        return render_template("buy.html", image = img)

@app.route("/history")
@login_required
def history():
    user = session["user_id"]
    img = session["img"]
    rows = db.execute("SELECT symbol, price, shares, time FROM transactions WHERE user = :user", user = user)
    return render_template("history.html", rows = rows, image = img)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["username"]
        session["img"] = rows[0]["image"]

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
    img = session["img"]
    if request.method == "POST":
        symb = request.form.get("symbol")
        response = lookup(symb)
        return render_template("quoted.html", name = response["name"], price = response["price"], symbol = response["symbol"], image = img)
    else:
        return render_template("quote.html", image = img)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        image = request.form.get("image")

        if not image:
            image = "https://cdn.discordapp.com/emojis/596131946363355146.gif?v=1"

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 403)

        elif not request.form.get("confirmation") or request.form.get("confirmation") != password:
            return apology("password not confirmed", 403)

        # Query database for username
        rows = db.execute("SELECT count(username) FROM users WHERE username = :username",
                          username=username)

        # Ensure username exists and password is correct
        if rows == 1:
            return apology("username taken", 403)
        else:
            password_hash = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash, cash, image) VALUES (:username, :hash, :cash, :image)", username=username, hash=password_hash, cash=10000, image = image)

        # Redirect user to home page
        return redirect("/login")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user = session["user_id"]
    img = session["img"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        iShares = request.form.get("shares")
        time = datetime.now()
        shares = db.execute("SELECT shares FROM stocks WHERE user = :user AND symbol = :symbol", user = user, symbol = symbol)
        cash = db.execute("SELECT cash FROM users WHERE username = :user", user = user)
        verify = db.execute("SELECT count(name) AS count FROM stocks WHERE user = :user AND symbol = :symbol", user = user, symbol = symbol)
        if verify[0]["count"] != 1:
            return apology("You do not own this stock!", 403)
        elif shares[0]["shares"] < int(iShares) or int(iShares) < 1:
            return apology("Invalid Amount of Shares!", 403)
        else:
            response = lookup(symbol)
            newCash = response["price"] * int(iShares) + cash[0]["cash"]
            db.execute("UPDATE users SET cash = :cash WHERE username = :user", cash = newCash, user = user)
            if shares[0]["shares"] == int(iShares):
               db.execute("DELETE FROM stocks WHERE user = :user AND symbol = :symbol", user = user, symbol = symbol)
               db.execute("INSERT INTO transactions (user, name, symbol, price, shares, time) VALUES (:user, :name, :symbol, :price, :shares, :time)", user = user, name = response["name"], symbol = symbol, price = response["price"], shares = "-"+iShares, time = time)
               return redirect("/")
            else:
                newShares = shares[0]["shares"] - int(iShares)
                db.execute("UPDATE stocks SET shares = :shares WHERE user = :user AND symbol = :symbol", shares = newShares, user = user, symbol = symbol)
                db.execute("INSERT INTO transactions (user, name, symbol, price, shares, time) VALUES (:user, :name, :symbol, :price, :shares, :time)", user = user, name = response["name"], symbol = symbol, price = response["price"], shares = "-"+iShares, time = time)
                return redirect("/")
    else:
        symbol = request.args.get('q')
        if symbol != "Symbol" and symbol != "":
            shares = db.execute("SELECT shares FROM stocks WHERE user = :user AND symbol = :symbol", user = user, symbol = symbol)
            return render_template("sell.html", symbol = symbol, shares = shares[0]["shares"], image = img)
        else:
            shares = "Shares"
            symbol = "Symbol"
            return render_template("sell.html", symbol = symbol, shares = shares, image = img)

@app.route("/money", methods=["GET", "POST"])
@login_required
def money():
    user = session["user_id"]
    img = session["img"]
    cash = db.execute("SELECT cash FROM users WHERE username = :username", username = user)
    today = datetime.today()
    if request.method == "POST":
        #datem = datetime(today.month, today.year)
        deposit = request.form.get("deposit")
        num = int(request.form.get("num"))
        expM = int(request.form.get("expM"))
        expY = int(request.form.get("expY"))
        cvv = request.form.get("CVV")

        if expM == None or expY == None:
            return apology("Expiration Not Found", 404)

        if expM >= today.month and expY >= today.year:
            return apology("Expiration Date Invalid")

        if cvv == None:
            return apology("CVV Not Found", 404)

        if len(cvv) != 3:
            return apology("CVV Not Valid", 400)

        valid = False
        i = 0

        numS = num

        while num != 0:
            num = (num - num % 10) / 10
            i += 1

        num = numS
        test = []

        for x in range(i):
            test.append(num % 10)
            num = (num - num % 10) / 10

        checkSum = 0

        for x in range(i):
            if x % 2 != 0:
                current = test[x] * 2
                if current > 9:
                    current1 = current % 10
                    current2 = (current - current % 10) / 10
                    checkSum = checkSum + current1 + current2
                else:
                    checkSum = checkSum + current
            else:
                checkSum = checkSum + test[x]

        print(checkSum % 10)
        print(checkSum)
        if checkSum % 10 == 0:
            newCash = cash[0]["cash"] + int(deposit)
            db.execute("UPDATE users SET cash = :cash WHERE username = :username", cash = newCash, username = user)
            return redirect("/")

        return apology("Card Not Valid", 400)
    else:
        return render_template("money.html", cash = cash[0]["cash"], year = today.year, year2 = today.year + 4, image = img)

@app.route("/profile", methods=["GET", "POST"])
@login_required
def profile():
    user = session["user_id"]
    img = session["img"]
    return render_template("profile.html", username = user, image = img)

@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    user = session["user_id"]
    img = session["img"]
    if request.method == "POST":
        password = request.form.get("password")
        cpassword = request.form.get("current")
        image = request.form.get("image")
        if not password:
            return apology("must provide password", 403)
        elif not cpassword:
            return apology("missing current password", 403)

        rows = db.execute("SELECT hash FROM users WHERE username = :user", user = user)

        if check_password_hash(rows[0]["hash"], cpassword):
            password_hash = generate_password_hash(password)
            db.execute("UPDATE users SET hash = :hash WHERE username = :user", hash = password_hash, user=user)
            return redirect("/profile")
        else:
            return apology("Error Incorrect Password. code: misshape")
    else:
        return render_template("password.html", image = img)

@app.route("/image", methods=["GET", "POST"])
@login_required
def image():
    user = session["user_id"]
    img = session["img"]
    if request.method == "POST":
        image = request.form.get("image")
        if not image:
            return apology("must provide an image link", 403)
        else:
            db.execute("UPDATE users SET image = :image WHERE username = :user", image = image, user=user)
            session["img"] = image
            return redirect("/profile")
    else:
        return render_template("image.html", image = img)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
