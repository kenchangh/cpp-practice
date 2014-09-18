# -*- coding: utf-8 -*-
"""
    casper.lib.hot_score
    ~~~~~~~~~

    Defines the 'hot' function to calculate hot scores of confessions.
"""

from math import log10
from datetime import datetime


def epoch_seconds(date):
    """Takes datetime object and returns total epoch seconds"""
    seconds = (date - datetime(1970, 1, 1)).total_seconds()
    return seconds


def score_rate(score, seconds):
    """
    The rate of acquiring scores per hour.
    score_rate = score / hours elapsed

    Takes in created time in Epoch seconds.
    Outputs score frequency.
    """
    minutes, seconds = divmod(seconds, 60)
    hours, minutes = divmod(minutes, 60)

    try:
        rate = score / hours
    except ZeroDivisionError:
        rate = 0

    return rate


def hot(score, created, comments):
    """
    Calculates hot score based on score (votes), recent-ness of, amount of comments,
    frequency of scores and user's reputation.
    """
    # Epoch seconds at start of use of algorithm
    START_TIME = 1407170715.44

    try:
        # Log requires absolute values
        log_score = log10(abs(score))
    # Raised when score is 0
    except ValueError:
        log_score = score

    # To reassign the sign after absolute
    # This is because value has to be log-ed
    if score > 0:
        sign = 1
    elif score < 0:
        sign = -1
    else:
        sign = 0

    # Time elapsed from created time
    # Until time algorithm was started to implement
    seconds = epoch_seconds(created) - START_TIME

    return round((log_score * sign * 5000
                  + seconds + comments +
                  score_rate(score, seconds)), 5) 

