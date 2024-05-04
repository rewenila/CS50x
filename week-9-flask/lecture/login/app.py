from flask import Flask, redirect, render_template, request, session
from flask_session import Session

app = Flask(__name__)

# Configure session
app.config["SESSION_PERMANENT"] = False # session ends when browser is closed
app.config["SESSION_TYPE"] = "filesystem" # session content is stored in a server's file and not on the cookie itself
Session(app) # activate session


@app.route("/")
def index():
    return render_template("index.html", name = session.get("name"))


@app.route("/login", methods = ["GET", "POST"])
def login():
    if request.method == "POST":
        session["name"] = request.form.get("name")
        return redirect("/")
    return render_template("login.html")


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")
