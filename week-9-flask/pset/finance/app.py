import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import logging

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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

    # Get user stocks (symbols and number of shares)
    user_stocks = get_user_stocks(session["user_id"])

    # Get user portfolio and total value in stocks
    user_portfolio, value_in_stocks = get_user_portfolio(user_stocks)

    # Get balance details
    user_balance = get_user_balance(session["user_id"], value_in_stocks)

    # Display table with transactions information
    return render_template("index.html", user_portfolio=user_portfolio, user_balance=user_balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get values from form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure stock symbol was submitted
        if not symbol:
            return apology("must provide stock symbol", 400)

        # Ensure number of shares is an integer number
        try:
            shares = int(shares)
        except ValueError:
            return apology("number of shares must be an integer number", 400)

        # Ensure number of shares is an integer number
        if shares < 0:
            return apology("number of shares must be a positive number", 400)

        # Look up stock current price
        quote = lookup(symbol)

        # Check that lookup() found stock price
        if not quote:
            return apology("invalid stock symbol", 400)

        # Calculate purchase amount
        total_amount = quote["price"] * shares

        # Check that the user has enough cash
        cash = get_user_cash(session["user_id"])
        if cash < total_amount:
            return apology("insufficient cash", 400)

        # Register purchase
        db.execute("INSERT INTO transactions (user_id, type, stock_symbol, stock_shares, total_amount) VALUES(?, ?, ?, ?, ?)",
                   session["user_id"], 'purchase', symbol.upper(), shares, total_amount)

        # Update user's cash
        updated_cash = cash - total_amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, session["user_id"])

        # Redirect to user home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Display form to buy a stock
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get transactions history from database
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])

    # Check if user already made a transaction
    if not transactions:
        return apology("user did not made any transaction yet")

    # Display table with transactions information
    return render_template("history.html", transactions=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)

        # Look up stock current price
        quote = lookup(request.form.get("symbol"))

        # Check that lookup found stock price
        if not quote:
            return apology("invalid stock symbol", 400)

        # Show quoted page
        return render_template("quoted.html", quote=quote)

    # User reached route via GET (as by clicking a link or via redirect)
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
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        # Ensure password and password confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure that the user is not already registered
        if len(rows) == 1:
            return apology("user already exists, please log in", 400)

        # Insert user information on database
        username = request.form.get("username")
        hashed_password = generate_password_hash(request.form.get("password"))
        id = db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                        username, hashed_password)

        # Log user in
        session["user_id"] = id

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_stocks = get_user_stocks(session["user_id"])

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get values from form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure stock symbol was submitted
        if not symbol:
            return apology("must provide stock symbol", 403)

        # Ensure number of shares is a positive number
        try:
            shares = int(shares)
        except ValueError:
            return apology("number of shares must be a positive number", 403)

        # Look up stock current price
        quote = lookup(symbol)

        # Check that lookup() found stock price
        if not quote:
            return apology("invalid stock symbol", 403)

        # Ensure user has shares of the selected stock
        if symbol not in user_stocks:
            return apology("you do not have shares of this stock")

        # Ensure user has sufficient shares of the selected stock
        if user_stocks[symbol] < shares:
            return apology("insuficient shares")

        # Calculate sale amount
        total_amount = quote["price"] * shares

        # Register purchase
        db.execute("INSERT INTO transactions (user_id, type, stock_symbol, stock_shares, total_amount) VALUES(?, ?, ?, ?, ?)",
                   session["user_id"], 'sale', symbol.upper(), shares, total_amount)

        # Get user's current cash
        cash = get_user_cash(session["user_id"])

        # Update user's cash
        updated_cash = cash + total_amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, session["user_id"])

        # Redirect to user home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Display form to buy a stock
        return render_template("sell.html", user_stocks=user_stocks)


def get_user_cash(id):
    """Get user stocks"""

    # Search users table
    cash = db.execute("SELECT cash FROM users WHERE id = ?", id)[0]["cash"]
    return cash


def get_user_stocks(id):
    """Get user stocks"""

    # Search transactions table
    rows = db.execute(
        "SELECT type, stock_symbol, stock_shares FROM transactions WHERE user_id = ?", id)

    # Iterate over rows to populate stocks dictionary
    user_stocks = {}
    for row in rows:
        stock_symbol = row["stock_symbol"]
        stock_shares = row["stock_shares"]
        type = row["type"]

        if stock_symbol not in user_stocks:
            if type == 'purchase':
                user_stocks[stock_symbol] = stock_shares
            else:
                user_stocks[stock_symbol] = -stock_shares
        else:
            if type == 'purchase':
                user_stocks[stock_symbol] += stock_shares
            else:
                user_stocks[stock_symbol] -= stock_shares

    # Return stocks dictionary
    return user_stocks


def get_user_portfolio(user_stocks):
    """Get user portfolio"""

    portfolio = []
    total_value = 0

    # Iterate over user's stocks
    for stock_symbol in user_stocks:

        # Calculate shares value
        shares = user_stocks[stock_symbol]
        price = lookup(stock_symbol)["price"]
        value = shares * price

        # Update total value
        total_value += value

        # Create dictionary of stock info
        stock_info = {
            "symbol": stock_symbol,
            "shares": shares,
            "price": price,
            "value": value
        }

        # Append to portfolio
        portfolio.append(stock_info)

    return portfolio, total_value


def get_user_balance(id, value_in_stocks):
    """Get user portfolio"""

    # Get total cash
    cash = get_user_cash(id)

    # Calculate total balance
    balance = cash + value_in_stocks

    # Create dictionary with balance details
    balance_details = {
        "cash": cash,
        "stocks": value_in_stocks,
        "balance": balance
    }

    return balance_details
