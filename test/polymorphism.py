# Test script for stepping through creation of a Python object in Boost Python
from polymorphism_ext import A

input("Press enter")
a = A.create()
print(type(a))
