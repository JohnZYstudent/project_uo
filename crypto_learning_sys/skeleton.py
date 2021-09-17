from flask import Flask, render_template, request, jsonify
from RSA import rsa
from DH import diffie_hellman
from Elgamal import elgamal
app = Flask(__name__)


@app.route("/")
def index():
    return render_template('mainpage.html')


@app.route("/process", methods=['POST'])
def process():
    # [p, q, N, r, e, publicKey, encryptedMsg, d, privateKey, decryptedMsg]
    e = request.form['userInput1']
    p = request.form['userInput2']
    q = request.form['userInput3']
    number = request.form['userInput4']
    if e and p and q:
        steps = rsa(e, p, q, number)
        return jsonify(steps)
    else:
        return jsonify("Error")


@app.route("/process1", methods=['POST'])
def process1():
    # return ["0"] if p is not prime
    # else return a list:
    # [p, g, a, b, A, B, A', B']
    p = request.form['userInput1']
    g = request.form['userInput2']
    a = request.form['userInput3']
    b = request.form['userInput4']
    if p and g and a and b:
        steps = diffie_hellman(p, g, a, b)
        return jsonify(steps)
    else:
        return jsonify("Error")


@app.route("/process2", methods=['POST'])
def process2():
    # return ["0"] if p is not prime
    # return [p, g, "0"] if a is not valid
    # else return a
    # list:
    # [p, g, a, publicKeyA, k, message, encryptedMsg, decryptedMsg]
    # example:
    # ['23333', '233', '776', '19729', '456', '345', '(16065, 19636)', '345']
    p = request.form['userInput1']
    g = request.form['userInput2']
    a = request.form['userInput3']
    k = request.form['userInput4']
    m = request.form['userInput5']
    if p and g and a and k and m:
        steps = elgamal(p, g, a, k, m)
        return jsonify(steps)
    else:
        return jsonify("Error")



if __name__ == "__main__":
    # Running standalone
    app.run(debug=True, host="0.0.0.0")
