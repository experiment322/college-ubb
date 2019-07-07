"""Module containing utility functions"""


from math import sqrt


def is_prime(num):
    """
    Return True if num is prime else False.
    """
    if num < 2:
        return False
    for i in range(2, int(sqrt(num)) + 1):
        if num % i == 0:
            return False
    return True


def satisfies_relation(num1, num2, rel):
    """
    Return True if num1 rel num2 is true, where rel is an integer denoting the relation.
    * negative `<`
    * positive `>`
    * null `=`
    """
    if rel < 0:
        return num1 < num2
    if rel > 0:
        return num1 > num2
    return num1 == num2
