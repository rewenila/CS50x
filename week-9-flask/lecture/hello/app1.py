from flask import Flask, render_template, request

app = Flask(__name__) # refers to the current file's name

@app.route("/")
def index():
    # if "name" in request.args:
    #     name = request.args["name"]
    # else:
    #     name = "World"
    # name = request.args.get("name", "World")
    # return render_template("index.html", name = name)
    return render_template("index.html")

# @app.route("/greet")
# def greet():
#     name = request.args.get("name", "World")
#     return render_template("greet.html", name = name)

@app.route("/greet", methods=["POST"])
def greet():
    name = request.form.get("name", "World")
    return render_template("greet.html", name = name)
