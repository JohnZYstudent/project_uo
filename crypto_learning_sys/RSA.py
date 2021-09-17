"""
Author: Missy Shi
Description: Implementation of RSA Key Exchange
Date: 11/03/2020
"""

# ------------------------------------- Function Declaration ------------------------------------- #
# prime_check(a: int) -> bool
# egcd(e: int, r: int) -> int
# gcdEx(a: int, b: int) -> (int, int, int)
# mul_inverse(e: int, r: int) -> int
# rsa_encrypt(public: tuple, m: int) -> int
# rsa_decrypt(private: int, c: int) -> int
# rsa(p: int, q: int, e: int, message: int) -> list
# ------------------------------------------------------------------------------------------------ #


def prime_check(a: int) -> bool:
    """ check for a integer is prime or not """
    if a == 2:
        return True
    elif (a < 2) or ((a % 2) == 0):
        return False
    elif a > 2:
        for i in range(2, a):
            if not (a % i):
                return False
    return True


def fast_powering(n: int, pow: int, modulus: int) -> int:
    """ Implementation of fast powering algorithm
    :param n: base integer
    :param pow: exponent
    :param modulus: integer modulus
    :return: res = n**pow (mod modulus)
    """
    res = 1
    n = n % modulus
    while pow > 0:
        if int(pow) & 1:
            res = (res * n) % modulus
        pow = int(pow) >> 1
        n = (n * n) % modulus
    return res


def egcd(e: int, r: int) -> int:
    """ gcd(e,(p-1)(q-1)) = 1 """
    while r != 0:
        e, r = r, e % r
    return e


def gcdEx(a: int, b: int) -> (int, int, int):
    """ Extended Euclidean Algorithm """
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = gcdEx(b % a, a)
        return (g, x - (b // a) * y, y)


def mul_inverse(e: int, r: int) -> int:
    """
    Find the multiplicative inverse of e (d) mod r
    r = (p-1)(q-1)
    ed = 1 (mod r)
    :param e: integer
    :param r: modulus
    :return: integer e^(-1) (mod r)
    """
    g, x, y = gcdEx(e, r)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % r


def rsa_encrypt(public: tuple, m: int) -> int:
    """return encrypted message"""
    N, e = public
    # ciphertext = (m ** e) % N
    ciphertext = fast_powering(m, e, N)
    return ciphertext


def rsa_decrypt(private: int, c: int) -> int:
    """return decrypted message"""
    d, N = private
    # plaintext = (c ** d) % N
    plaintext = fast_powering(c, d, N)
    return plaintext


def rsa(p: str, q: str, e: str, message: str) -> list:
    """
    return ["0", q] if p is not prime
    return [p, "0"] if q is not prime
    return ["0", "0"] if p and q both are not prime
    return [p, q, N, r, "0"] if e is not valid
    else return:
    [p, q, N, r, e, publicKey, message, encryptedMsg, d, privateKey, decryptedMsg]
    """
    result = []
    p = int(p)
    q = int(q)
    e = int(e)
    message = int(message)
    # Input prime numbers p & q, Check if inputs are prime #
    # if not prime, return False, and ask to input again #
    # p = int(input("Enter a prime number for p: "))
    check_p = prime_check(p)
    if check_p == False:
        result.append("0")
    else:
        result.append(str(p))

    # Input prime numbers q & Check if inputs are prime #
    # q = int(input("Enter a prime number for q: "))
    check_q = prime_check(q)
    if check_q == False:
        result.append("0")
    else:
        result.append(str(q))

    # if p or q is not prime, return a small list #
    if result[0] == "0" or result[1] == "0":
        return result

    #  Calculation of RSA modulus N #
    n = p * q
    result.append(str(n))

    # Calculation of Eulers toitent 'r' #
    r = (p-1)*(q-1)
    result.append(str(r))

    # 'e' Value Calculation #
    # e = int(input("Enter an exponent e between 1 and 1000: "))
    check_e = egcd(e, r)
    if check_e != 1:
        result.append("0")
        return result
    else:
        result.append(str(e))

    # Public key: publish N = pq and e #
    public = (n, e)
    result.append(str(public))

    # input message #
    # message = int(input("What would you like to encrypt or decrypt?: "))
    # print(f"Your message is: {message}")
    result.append(str(message))

    # encrypt message #
    enc_msg = rsa_encrypt(public, message)
    result.append(str(enc_msg))

    # Private key: d and N = pq (keep d private) #
    d = mul_inverse(e, r)
    result.append(str(d))

    private = (d, n)
    result.append(str(private))

    # decrypt message #
    dec_msg = rsa_decrypt(private, enc_msg)
    result.append(str(dec_msg))

    return result


def main():
    print(rsa("10859","155797","97","100"))


if __name__ == "__main__":
    main()