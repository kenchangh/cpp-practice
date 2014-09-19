#! /c/Python27/python

from distutils.core import setup, Extension
setup(name='hot_score', version='1.0',
      ext_modules=[Extension('hot_score', ['hot.cpp'])])